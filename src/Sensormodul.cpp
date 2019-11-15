#define SEALEVELPREASURE_HPA (1013.25)

#ifndef __linux__
// #include <Adafruit_BME280.h>
// #include <Adafruit_Sensor.h>
// #include <ClosedCube_HDC1080.h>
// #include <SparkFun_SCD30_Arduino_Library.h>
#include "SensorHDC1080.h"
#include "SensorBME280.h"
#include "SensorSCD30.h"
#endif

// Reihenfolge beachten damit die Definitionen von Sensormodul.h ...
#include "Sensormodul.h"
// ... auf jeden Fall Vorrang haben (beeinflussen auch die Logik)
#include "../../knx-logic/src/LogikmodulCore.h"

// Achtung: Bitfelder in der ETS haben eine gewöhnungswürdige
// Semantik: ein 1 Bit-Feld mit einem BitOffset=0 wird in Bit 7(!) geschrieben
#define BIT_1WIRE 1
#define BIT_Temp 2
#define BIT_Hum 4
#define BIT_Pre 8
#define BIT_Voc 16
#define BIT_Co2 32
#define BIT_RESERVE 64
#define BIT_LOGIC 128

#define SENSOR_HDC1080 0x06
#define SENSOR_BME280 0x0E
#define SENSOR_BME680 0x1E
#define SENSOR_CO2 0x26
#define SENSOR_CO2_BME280 0x2E
#define SENSOR_CO2_BME680 0x3E
#define SENSOR_FILTER_INT 0x7E

#ifdef __linux__
extern KnxFacade<LinuxPlatform, Bau57B0> knx;
#endif

// runtime information for the whole logik module
struct sSensorInfo
{
    // double currentValue;
    unsigned long sendDelay;
    unsigned long readDelay;
};

struct sRuntimeInfo
{
    uint16_t currentPipeline;
    sSensorInfo temp;
    sSensorInfo hum;
    sSensorInfo pre;
    sSensorInfo voc;
    sSensorInfo co2;
    sSensorInfo dew;
    sSensorInfo wire[8];
    unsigned long startupDelay;
    unsigned long heartbeatDelay;
};

sRuntimeInfo gRuntimeData;
uint8_t gSensor = 0;

typedef bool (*getSensorValue)(MeasureType, double&);

uint16_t getError() {
    return (uint16_t)knx.getGroupObject(LOG_KoError).value(getDPT(VAL_DPT_7));
}

void setError(uint16_t iValue) {
    knx.getGroupObject(LOG_KoError).valueNoSend(iValue, getDPT(VAL_DPT_7));
}

void sendError() {
    knx.getGroupObject(LOG_KoError).objectWritten();
}

// Starting all required sensors, this call may be blocking (with delay)
void StartSensor()
{
#ifdef __linux__
    return true;
#else
    Sensor* lSensor;
    // bool lResult = true;
    uint8_t lMeasureTypes;
    // uint16_t lError = (uint16_t)knx.getGroupObject(LOG_KoError).value(getDPT(VAL_DPT_7));
    uint8_t lSensorFlags = gSensor & SENSOR_FILTER_INT;
    if (lSensorFlags == SENSOR_HDC1080)
    {
        lMeasureTypes = static_cast<MeasureType>(Temperature | Humidity);
        lSensor = new SensorHDC1080(lMeasureTypes, 0x40);
        lSensor->begin();
    }
    if (lSensorFlags == SENSOR_BME280 || lSensorFlags == SENSOR_CO2_BME280)
    {
        lMeasureTypes = static_cast<MeasureType>(Temperature | Humidity | Pressure);
        lSensor = new SensorBME280(lMeasureTypes, 0x76);
        lSensor->begin();
    }
    if (lSensorFlags == SENSOR_CO2)
    {
        lMeasureTypes = static_cast<MeasureType>(Temperature | Humidity | Co2);
        lSensor = new SensorSCD30(lMeasureTypes, 0x61);
        lSensor->begin();
    }
    // if (lError > 0 && (knx.paramByte(LOG_Error) & 128) > 0)
    // {
    //     knx.getGroupObject(LOG_KoError).value(lError, getDPT(VAL_DPT_7));
    // }
    // return lResult;
#endif
}
bool ReadSensorValue(MeasureType iMeasureType, double& eValue) {
    return Sensor::measureValue(iMeasureType, eValue);
}

// generic sensor processing
void ProcessSensor(sSensorInfo *cData, getSensorValue fGetSensorValue, MeasureType iMeasureType, double iOffsetFactor, double iValueFactor, uint16_t iParamIndex, uint16_t iKoNumber, bool iForce = false)
{
    bool lSend = iForce;
    // process send cycle
    uint32_t lCycle = knx.paramInt(iParamIndex + 1) * 1000;

    // we waited enough, let's send the value
    if (lCycle && millis() - cData->sendDelay > lCycle)
        lSend = true;

    // process read cycle
    if (iForce || millis() - cData->readDelay > 5000)
    {
        // we waited enough, let's read the sensor
        int32_t lOffset = (int8_t)knx.paramByte(iParamIndex);
        double lValue;
        bool lValid = fGetSensorValue(iMeasureType, lValue);
        if (lValid) {
            lValue += (lOffset / iOffsetFactor);
            lValue = lValue / iValueFactor;
            // smoothing (? glätten ?) of the new value
            lValue = (double)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9)) + (lValue - (double)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9))) / knx.paramByte(iParamIndex + 8);
            // evaluate sending conditions (relative delta / absolute delta)
            double lDelta = 100.0 - lValue / (double)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9)) * 100.0;
            uint32_t lPercent = knx.paramByte(iParamIndex + 7);
            if (lPercent && (uint32_t)abs(lDelta) >= lPercent)
                lSend = true;
            float lAbsolute = knx.paramWord(iParamIndex + 5) / iOffsetFactor;
            if (lAbsolute > 0.0 && abs(lValue - (float)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9))) >= lAbsolute)
                lSend = true;
            // we always store the new value in KO, even it it is not sent (to satisfy potential read request)
            knx.getGroupObject(iKoNumber).valueNoSend(lValue, getDPT(VAL_DPT_9));
        }
        cData->readDelay = millis();
    }
    if (lSend)
    {
        if ((getError() & iMeasureType) == 0) knx.getGroupObject(iKoNumber).objectWritten();
        cData->sendDelay = millis();
    }
}

struct sPoint
{
    double x;
    double y;
};

sPoint comfort1[8] = {{17, 88.8}, {21.4, 84.1}, {25, 60}, {27.1, 30.5}, {25.9, 29.5}, {20, 29.5}, {17.1, 48.8}, {15.9, 78.8}};
sPoint comfort2[4] = {{17.5, 74.7}, {22, 72.9}, {24.3, 37.6}, {18.9, 41.8}};

bool InPolygon(sPoint *iPoly, uint8_t iLen, double iX, double iY)
{

    int j = iLen - 1;
    bool lResult = false;
    for (int i = 0; i < iLen; i++)
    {
        if (((iPoly[i].y > iY) != (iPoly[j].y > iY)) && (iX < (iPoly[j].x - iPoly[i].x) * (iY - iPoly[i].y) / (iPoly[j].y - iPoly[i].y) + iPoly[i].x))
        {
            lResult = !lResult;
        }
        j = i;
    }
    return lResult;
}

// Dewpoint is a vitual sensor and might be implemented on sensor class level, but we implement it here (easier and shorter)
bool CalculateDewValue(MeasureType iMeasureType, double& eValue) {
    double lTemp = knx.getGroupObject(LOG_KoTemp).value(getDPT(VAL_DPT_9)); //gRuntimeData.temp.currentValue;
    double lHum = knx.getGroupObject(LOG_KoHum).value(getDPT(VAL_DPT_9));   //gRuntimeData.hum.currentValue;
    double lLogHum = log(lHum / 100.0);
    eValue = 243.12 * ((17.62 * lTemp) / (243.12 + lTemp) + lLogHum) / ((17.62 * 243.12) / (243.12 + lTemp) - lLogHum);
    return true;
}

void CalculateComfort(bool iForce = false)
{
    static uint32_t sMillis = 0;
    bool lSend = iForce;
    if (iForce || millis() - sMillis > 1000)
    {
        sMillis = millis();
        // do not calculate if underlying measures are corrupt
        if (getError() & (Temperature | Humidity)) return;

        double lTemp = knx.getGroupObject(LOG_KoTemp).value(getDPT(VAL_DPT_9)); //gRuntimeData.temp.currentValue;
        double lHum = knx.getGroupObject(LOG_KoHum).value(getDPT(VAL_DPT_9));   //gRuntimeData.hum.currentValue;
        if (knx.paramByte(LOG_Comfort) & 32)
        {
            // comfortzone
            uint8_t lComfort = 0;
            if (InPolygon(comfort2, 4, lTemp, lHum))
            {
                lComfort = 2;
            }
            else if (InPolygon(comfort1, 8, lTemp, lHum))
            {
                lComfort = 1;
            }
            if ((uint8_t)knx.getGroupObject(LOG_KoComfort).value(getDPT(VAL_DPT_5)) != lComfort)
                lSend = true;
            if (lSend)
                knx.getGroupObject(LOG_KoComfort).value(lComfort, getDPT(VAL_DPT_5));
        }
    }
}

// true solgange der Start des gesamten Moduls verzögert werden soll
bool startupDelay()
{
    return (millis() - gRuntimeData.startupDelay < knx.paramInt(LOG_StartupDelay) * 1000);
}

void ProcessHeartbeat()
{
    // the first heartbeat is send directly after startup delay of the device
    if (gRuntimeData.heartbeatDelay == 0 || millis() - gRuntimeData.heartbeatDelay > knx.paramInt(LOG_Heartbeat) * 1000)
    {
        // we waited enough, let's send a heartbeat signal
        knx.getGroupObject(LOG_KoHeartbeat).value(true, getDPT(VAL_DPT_1));
        // if there is an error, we send it with heartbeat, too
        if (knx.paramByte(LOG_Error) & 128)
        {
            if (getError()) sendError();
        }
        gRuntimeData.heartbeatDelay = millis();
        // debug-helper for logic module
        // print("ParDewpoint: ");
        // println(knx.paramByte(LOG_Dewpoint));
        logikDebug();
    }
}

void ProcessSensors(bool iForce = false)
{
    if (gSensor & BIT_Temp)
        ProcessSensor(&gRuntimeData.temp, ReadSensorValue, Temperature, 10.0, 1.0, LOG_TempOffset, LOG_KoTemp, iForce);
    if (gSensor & BIT_Hum)
        ProcessSensor(&gRuntimeData.hum, ReadSensorValue, Humidity, 1.0, 1.0, LOG_HumOffset, LOG_KoHum, iForce);
    if (gSensor & BIT_Pre)
        ProcessSensor(&gRuntimeData.pre, ReadSensorValue, Pressure, 1.0, 1.0, LOG_PreOffset, LOG_KoPre, iForce);
    if (gSensor & BIT_Co2)
        ProcessSensor(&gRuntimeData.co2, ReadSensorValue, Co2, 1.0, 1.0, LOG_Co2Offset, LOG_KoCo2, iForce);

    if ((gSensor & (BIT_Temp | BIT_Hum)) == (BIT_Temp | BIT_Hum)) {
        ProcessSensor(&gRuntimeData.dew, CalculateDewValue, static_cast<MeasureType>(Temperature | Humidity), 10.0, 1.0, LOG_DewOffset, LOG_KoDewpoint, iForce);
        CalculateComfort(iForce);
    }

    // error processing
    uint8_t lError = Sensor::getError();
    if (lError != getError()) {
        setError(lError);
        if (knx.paramByte(LOG_Error) & 128)
            sendError();
    }
}

void ProcessRequestValues(GroupObject &iKo)
{
    if (iKo.asap() == LOG_KoRequestValues) {
        println("Request values called");
        print("KO-Value is ");
        println((bool)iKo.value(getDPT(VAL_DPT_1)));
        if ((bool)iKo.value(getDPT(VAL_DPT_1)))
        {
            ProcessSensors(true);
        }
    }
}

bool gForceAtStartup = true;

void appLoop()
{
    if (!knx.configured())
        return;

    // handle KNX stuff
    if (startupDelay())
        return;

    // at this point startup-delay is done
    // we process heartbeat
    ProcessHeartbeat();

    // at Startup, we want to send all values immediately
    ProcessSensors(gForceAtStartup);
    gForceAtStartup = false;

    if (gSensor & BIT_LOGIC)
        logikLoop();

    Sensor::sensorLoop();
}

void appSetup(uint8_t iBuzzerPin, uint8_t iSavePin)
{

    gSensor = (knx.paramByte(LOG_SensorDevice));

    if (gSensor & BIT_LOGIC)
        logikSetup(iBuzzerPin, iSavePin);

    if (knx.configured())
    {
        gRuntimeData.startupDelay = millis();
        gRuntimeData.heartbeatDelay = 0;
        // GroupObject &lKoRequestValues = knx.getGroupObject(LOG_KoRequestValues);
        GroupObject::classCallback(ProcessRequestValues);
        StartSensor();
    }
}