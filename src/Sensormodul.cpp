#define SEALEVELPREASURE_HPA (1013.25)

#ifndef __linux__
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <ClosedCube_HDC1080.h>
#include <SparkFun_SCD30_Arduino_Library.h>
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
#else
ClosedCube_HDC1080 gHDC1080;
Adafruit_BME280 gBME280;
SCD30 gSCD30;

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
    sSensorInfo wire[8];
    unsigned long startupDelay;
    unsigned long heartbeatDelay;
};

sRuntimeInfo gRuntimeData;
uint8_t gSensor = 0;

typedef bool (*getSensorValue)(double&);

bool StartSensorBME280(uint16_t *iError)
{
    bool lResult = gBME280.begin(0x76);
    if (lResult)
    {
        println("BME280 successully started!");
    }
    else
    {
        *iError |= BIT_Temp | BIT_Hum | BIT_Pre;
        print("Error BME280: ");
        println(*iError);
    }
    return lResult;
}

bool StartSensorSCD30(uint16_t *iError)
{
    bool lResult = gSCD30.begin(); //This will cause readings to occur every two seconds
    if (lResult)
    {
        println("SCD30 successully started!");
    }
    else
    {
        *iError |= BIT_Temp | BIT_Hum | BIT_Co2;
        print("Error SCD30: ");
        println(*iError);
    }
    return lResult;
}

bool CheckSensorConnection(uint8_t iAddress)
{
    Wire.beginTransmission(iAddress);
    return (Wire.endTransmission() == 0);
}

// Stubs for specific sensor apis
bool StartSensor()
{
#ifdef __linux__
    return true;
#else
    bool lResult = true;
    uint16_t lError = (uint16_t)knx.getGroupObject(LOG_KoError).value(getDPT(VAL_DPT_7));
    switch (gSensor & SENSOR_FILTER_INT)
    {
        case SENSOR_HDC1080:
            lResult = true;
            gHDC1080.begin(0x40); //insert correct address here
            break;
        case SENSOR_BME280:
            lResult = StartSensorBME280(&lError);
            break;
        case SENSOR_CO2_BME280:
            lResult = StartSensorBME280(&lError);
            lResult &= StartSensorSCD30(&lError);
            break;
        case SENSOR_CO2:
            lResult = StartSensorSCD30(&lError);
            break;
        default:
            lResult = false;
            break;
    }
    if (lError > 0 && (knx.paramByte(LOG_Error) & 128) > 0)
    {
        knx.getGroupObject(LOG_KoError).value(lError, getDPT(VAL_DPT_7));
    }

    return lResult;
#endif
}

bool ReadTemperature(double& iValue)
{
#ifdef __linux__
    return 22.7;
#else
    switch (gSensor & SENSOR_FILTER_INT)
    {
        case SENSOR_HDC1080:
            iValue = gHDC1080.readTemperature();
            return true;
            break;
        case SENSOR_BME280:
            iValue = gBME280.readTemperature();
            return true;
            break;
        case SENSOR_CO2_BME280:
            // here we can decide if the temperature is taken from BME or SCD
            iValue = gSCD30.getTemperature();
            return true;
            break;
        case SENSOR_CO2:
            iValue = gSCD30.getTemperature();
            return true;
            break;
        default:
            return false;
            break;
    }
    iValue = -50.0;
    return true;
#endif
}

bool ReadHumidity(double& iValue)
{
#ifdef __linux__
    return 55.3;
#else
    switch (gSensor & SENSOR_FILTER_INT)
    {
        case SENSOR_HDC1080:
            iValue = gHDC1080.readHumidity();
            return true;
            break;
        case SENSOR_BME280:
            iValue = gBME280.readHumidity();
            return true;
            break;
        case SENSOR_CO2_BME280:
            // here we can decide if the humidity is taken from BME or SCD
            iValue = gSCD30.getHumidity();
            return true;
            break;
        case SENSOR_CO2:
            iValue = gSCD30.getHumidity();
            return true;
            break;
        default:
            return false;
            break;
    }
    iValue = -1.0;
    return true;
#endif
}

bool ReadPressure(double& iValue)
{
#ifdef __linux__
    return 1023.3;
#else
    switch (gSensor & SENSOR_FILTER_INT)
    {
        case SENSOR_BME280:
        case SENSOR_CO2_BME280:
            iValue = gBME280.readPressure();
            return true;
            break;
        default:
            return false;
            break;
    }
    iValue = -1.0;
    return true;
#endif
}

bool ReadCO2(double& iValue)
{
#ifdef __linux__
    return 1000;
#else
    switch (gSensor & SENSOR_FILTER_INT)
    {
        case SENSOR_CO2_BME280:
        case SENSOR_CO2:
            iValue = (double)gSCD30.getCO2();
            return true;
            break;
        default:
            return false;
            break;
    }
    iValue = -1.0;
    return true;
#endif
}

// generic sensor processing
void ProcessSensor(sSensorInfo *cData, getSensorValue fGetSensorValue, double iOffsetFactor, double iValueFactor, uint16_t iParamIndex, uint16_t iKoNumber, bool iForce = false)
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
        bool lValid = fGetSensorValue(lValue);
        lValue += (lOffset / iOffsetFactor);
        lValue = lValue / iValueFactor;
        // smoothing (? glätten ?) of the new value
        lValue = (double)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9)) + (lValue - (double)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9))) / knx.paramByte(iParamIndex + 8);
        // evaluate sending conditions
        double lDelta = 100.0 - lValue / (double)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9)) * 100.0;
        uint32_t lPercent = knx.paramByte(iParamIndex + 7);
        if (lPercent && (uint32_t)abs(lDelta) >= lPercent)
            lSend = true;
        float lAbsolute = knx.paramWord(iParamIndex + 5) / iOffsetFactor;
        if (lAbsolute > 0.0 && abs(lValue - (float)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9))) >= lAbsolute)
            lSend = true;
        // cData->currentValue = lValue;
        knx.getGroupObject(iKoNumber).valueNoSend(lValue, getDPT(VAL_DPT_9));
        cData->readDelay = millis();
    }
    if (lSend)
    {
        // knx.getGroupObject(iKoNumber).value(cData->currentValue);
        knx.getGroupObject(iKoNumber).objectWritten();
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

void ProcessCalculatedValues(bool iForce = false)
{
    static uint32_t sMillis = 0;
    bool lSend = iForce;
    if (iForce || millis() - sMillis > 1000)
    {
        double lTemp = knx.getGroupObject(LOG_KoTemp).value(getDPT(VAL_DPT_9)); //gRuntimeData.temp.currentValue;
        double lHum = knx.getGroupObject(LOG_KoHum).value(getDPT(VAL_DPT_9));   //gRuntimeData.hum.currentValue;
        if (knx.paramByte(LOG_Dewpoint) & 64)
        {
            // Taupunkt
            double lLogHum = log(lHum / 100.0);
            double lDewpoint = 243.12 * ((17.62 * lTemp) / (243.12 + lTemp) + lLogHum) / ((17.62 * 243.12) / (243.12 + lTemp) - lLogHum);
            if ((uint8_t)knx.getGroupObject(LOG_KoDewpoint).value(getDPT(VAL_DPT_9)) != (uint8_t)lDewpoint)
                lSend = true;
            if (lSend)
                knx.getGroupObject(LOG_KoDewpoint).value(lDewpoint, getDPT(VAL_DPT_9));
        }
        lSend = iForce;
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
        sMillis = millis();
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
        // if there is an error, we send it, too
        if (knx.paramByte(LOG_Error) & 128)
        {
            uint16_t lError = (uint16_t)knx.getGroupObject(LOG_KoError).value(getDPT(VAL_DPT_7));
            if (lError)
                knx.getGroupObject(LOG_KoError).value(lError, getDPT(VAL_DPT_7));
        }
        gRuntimeData.heartbeatDelay = millis();
        // debug-helber for logic module
        // print("ParDewpoint: ");
        // println(knx.paramByte(LOG_Dewpoint));
        logikDebug();
    }
}

void ProcessSensors(bool iForce = false)
{
    if (gSensor & BIT_Temp)
        ProcessSensor(&gRuntimeData.temp, ReadTemperature, 10.0, 1.0, LOG_TempOffset, LOG_KoTemp, iForce);
    if (gSensor & BIT_Hum)
        ProcessSensor(&gRuntimeData.hum, ReadHumidity, 1.0, 1.0, LOG_HumOffset, LOG_KoHum, iForce);
    if (gSensor & BIT_Pre)
        ProcessSensor(&gRuntimeData.pre, ReadPressure, 1.0, 1.0, LOG_PreOffset, LOG_KoPre, iForce);
    if (gSensor & BIT_Co2)
        ProcessSensor(&gRuntimeData.pre, ReadCO2, 1.0, 1.0, LOG_Co2Offset, LOG_KoCo2, iForce);

    if ((gSensor & (BIT_Temp | BIT_Hum)) == (BIT_Temp | BIT_Hum))
        ProcessCalculatedValues(iForce);
}

void ProcessRequestValues(GroupObject &iKo)
{
    println("Request values called");
    if (iKo.asap() == LOG_KoRequestValues) {
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
}

void appSetup()
{

    gSensor = (knx.paramByte(LOG_SensorDevice));

    if (gSensor & BIT_LOGIC)
        logikSetup();

    if (knx.configured())
    {
        gRuntimeData.startupDelay = millis();
        gRuntimeData.heartbeatDelay = 0;
        // init KO-DPTs
        // knx.getGroupObject(LOG_KoHeartbeat).dataPointType(Dpt(1, 2));
        // knx.getGroupObject(LOG_KoError).dataPointType(Dpt(7, 1));
        // knx.getGroupObject(LOG_KoTemp).dataPointType(Dpt(9, 1));
        // knx.getGroupObject(LOG_KoHum).dataPointType(Dpt(9, 7));
        // knx.getGroupObject(LOG_KoPre).dataPointType(Dpt(9, 6));
        // knx.getGroupObject(LOG_KoCo2).dataPointType(Dpt(9, 8));
        // knx.getGroupObject(LOG_KoDewpoint).dataPointType(Dpt(9, 1));
        // knx.getGroupObject(LOG_KoComfort).dataPointType(Dpt(5, 5));
        GroupObject &lKoRequestValues = knx.getGroupObject(LOG_KoRequestValues);
        // lKoRequestValues.dataPointType(Dpt(1, 1));
        lKoRequestValues.callback(ProcessRequestValues);
        StartSensor();
    }
}