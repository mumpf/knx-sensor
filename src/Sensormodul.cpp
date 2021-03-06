#define SEALEVELPREASURE_HPA (1013.25)

#ifndef __linux__
#include "SensorSHT3x.h"
#include "SensorBME280.h"
#include "SensorBME680.h"
#include "SensorSCD30.h"
#include "SensorIAQCore.h"
#endif

#include "Hardware.h"
// Reihenfolge beachten damit die Definitionen von Sensormodul.h ...
#include "Sensormodul.h"
// ... auf jeden Fall Vorrang haben (beeinflussen auch die Logik)
// #include "../../knx-logic/src/LogikmodulCore.h"
#include "Logic.h"

const uint8_t cFirmwareMajor = 2;    // 0-31
const uint8_t cFirmwareMinor = 4;    // 0-31
const uint8_t cFirmwareRevision = 0; // 0-63

// Achtung: Bitfelder in der ETS haben eine gewöhnungswürdige
// Semantik: ein 1 Bit-Feld mit einem BitOffset=0 wird in Bit 7(!) geschrieben
#define BIT_1WIRE 1
#define BIT_Temp 2
#define BIT_Hum 4
#define BIT_Pre 8
#define BIT_Voc 16
#define BIT_Co2 32
#define BIT_Co2Calc 64
#define BIT_LOGIC 128

#define SENSOR_SHT3X 1
#define SENSOR_BME280 2
#define SENSOR_BME280_CO2 3
#define SENSOR_BME680 4
#define SENSOR_BME680_CO2 5
#define SENSOR_CO2 6
#define SENSOR_CO2_BME280 7
#define SENSOR_CO2_BME680 8
#define SENSOR_IAQCORE 9
#define SENSOR_IAQCORE_SHT3X 10
#define SENSOR_IAQCORE_BME280 11
#define SENSOR_MASK 0x7E

#ifdef __linux__
extern KnxFacade<LinuxPlatform, Bau57B0> knx;
#endif

// runtime information for the whole logik module
struct sSensorInfo
{
    float lastSentValue = NAN;
    unsigned long sendDelay;
    unsigned long readDelay;
};

struct sRuntimeInfo
{
    bool isRunning = false;
    sSensorInfo temp;
    sSensorInfo hum;
    sSensorInfo pre;
    sSensorInfo voc;
    sSensorInfo co2;
    sSensorInfo co2b;
    sSensorInfo dew;
    sSensorInfo wire[8];
    unsigned long startupDelay;
    unsigned long heartbeatDelay;
    uint32_t saveInterruptTimestamp = 0;
    bool forceSensorRead = true;
};

sRuntimeInfo gRuntimeData;
uint8_t gSensor = 0;
Logic gLogic;

typedef bool (*getSensorValue)(MeasureType, float&);

uint16_t getError() {
    return (uint16_t)knx.getGroupObject(LOG_KoError).value(getDPT(VAL_DPT_7));
}

void setError(uint16_t iValue) {
    knx.getGroupObject(LOG_KoError).valueNoSend(iValue, getDPT(VAL_DPT_7));
}

void sendError() {
    knx.getGroupObject(LOG_KoError).objectWritten();
}

void ProcessHeartbeat()
{
    // the first heartbeat is send directly after startup delay of the device
    if (gRuntimeData.heartbeatDelay == 0 || delayCheck(gRuntimeData.heartbeatDelay, knx.paramInt(LOG_Heartbeat) * 1000))
    {
        // we waited enough, let's send a heartbeat signal
        knx.getGroupObject(LOG_KoHeartbeat).value(true, getDPT(VAL_DPT_1));
        // if there is an error, we send it with heartbeat, too
        if (knx.paramByte(LOG_Error) & 128) {
            if (getError()) sendError();
        }
        gRuntimeData.heartbeatDelay = millis();
        // The module prints its firmware version to the console
        printDebug("Firmware-Version [%d] %d.%d\n", cFirmwareMajor, cFirmwareMinor, cFirmwareRevision);
        // debug-helper for logic module
        // print("ParDewpoint: ");
        // println(knx.paramByte(LOG_Dewpoint));
        gLogic.debug();
    }
}

void ProcessReadRequests() {
    static uint8_t sCalled = 1;
    // the following code should be called only once
    gLogic.processReadRequests();
    if (sCalled < 255) {

        // we evaluate only Bit 2 here, which holds the information about read external values on startup
        if (delayCheck(gRuntimeData.startupDelay, 1000) && sCalled == 1) {
            sCalled += 1;
            if (knx.paramByte(LOG_TempExtRead) & 4) {
                knx.getGroupObject(LOG_KoExt1Temp).requestObjectRead();
                knx.getGroupObject(LOG_KoExt2Temp).requestObjectRead();
            }
        }
        if (delayCheck(gRuntimeData.startupDelay, 2000) && sCalled == 2)
        {
            sCalled += 1;
            if (knx.paramByte(LOG_HumExtRead) & 4)
            {
                knx.getGroupObject(LOG_KoExt1Hum).requestObjectRead();
                knx.getGroupObject(LOG_KoExt2Hum).requestObjectRead();
            }
        }
        if (delayCheck(gRuntimeData.startupDelay, 3000) && sCalled == 3)
        {
            sCalled += 1;
            if (knx.paramByte(LOG_PreExtRead) & 4)
            {
                knx.getGroupObject(LOG_KoExt1Pre).requestObjectRead();
                knx.getGroupObject(LOG_KoExt2Pre).requestObjectRead();
            }
        }
        if (delayCheck(gRuntimeData.startupDelay, 4000) && sCalled == 4)
        {
            sCalled += 1;
            if (knx.paramByte(LOG_VocExtRead) & 4) {
                knx.getGroupObject(LOG_KoExt1VOC).requestObjectRead();
                knx.getGroupObject(LOG_KoExt2VOC).requestObjectRead();
            }
        }
        if (delayCheck(gRuntimeData.startupDelay, 5000) && sCalled == 5)
        {
            sCalled = 255;
            if (knx.paramByte(LOG_Co2ExtRead) & 4)
            {
                knx.getGroupObject(LOG_KoExt1Co2).requestObjectRead();
                knx.getGroupObject(LOG_KoExt2Co2).requestObjectRead();
            }
        }
    }
}

// this callback is used by BME680 during delays while mesauring
// we implement this delay, but keep normal loop processing alive
void sensorDelayCallback(uint32_t iMillis) {
    // printDebug("sensorDelayCallback: Called with a delay of %lu ms\n", iMillis);
    uint32_t lMillis = millis();
    while (millis() - lMillis < iMillis) {
        if (gRuntimeData.isRunning) {
            knx.loop();
            ProcessHeartbeat();
            gLogic.loop();
        }
    }
    // printDebug("sensorDelayCallback: Left after %lu ms\n", millis() - lMillis);
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
    // uint16_t lError = (uint16_t)knx.getGroupObject(LOG_KoError).value(getDpt(VAL_DPT_7));
    uint8_t lSensorInstalled = (knx.paramByte(LOG_SensorDevice) & SENSOR_MASK) >> 1;
    // usually all sensors have temp and hum
    gSensor = (lSensorInstalled) ? BIT_Temp | BIT_Hum : 0;
    if (lSensorInstalled == SENSOR_SHT3X || lSensorInstalled == SENSOR_IAQCORE_SHT3X)
    {
        lMeasureTypes = static_cast<MeasureType>(Temperature | Humidity);
        lSensor = new SensorSHT3x(lMeasureTypes, 0x44);
        lSensor->begin();
    }
    if (lSensorInstalled == SENSOR_BME280 || lSensorInstalled == SENSOR_BME280_CO2 || lSensorInstalled == SENSOR_CO2_BME280 || lSensorInstalled == SENSOR_IAQCORE_BME280)
    {
        gSensor |= BIT_Pre;
        lMeasureTypes = static_cast<MeasureType>(Pressure | Temperature | Humidity);
        lSensor = new SensorBME280(lMeasureTypes, 0x76);
        lSensor->begin();
    }
    if (lSensorInstalled == SENSOR_BME680 || lSensorInstalled == SENSOR_BME680_CO2 || lSensorInstalled == SENSOR_CO2_BME680)
    {
        uint8_t lMagicWordOffset = knx.paramByte(LOG_DeleteData) & 4;
        gSensor |= BIT_Pre | BIT_Voc | BIT_Co2Calc;
        // in case temp, hum shoud be taken from co2 sensor, we remove them from known measure types
        lMeasureTypes = static_cast<MeasureType>(Pressure | Voc | Accuracy | Co2Calc |  Temperature | Humidity);
        lSensor = new SensorBME680(lMeasureTypes, 0x76, sensorDelayCallback, lMagicWordOffset);
        lSensor->begin();
    }
    if (lSensorInstalled == SENSOR_CO2 || lSensorInstalled == SENSOR_CO2_BME280 || lSensorInstalled == SENSOR_BME280_CO2 || lSensorInstalled == SENSOR_CO2_BME680 || lSensorInstalled == SENSOR_BME680_CO2)
    {
        gSensor |= BIT_Co2;
        lMeasureTypes = static_cast<MeasureType>(Temperature | Humidity | Co2);
        lSensor = new SensorSCD30(lMeasureTypes, 0x61);
        lSensor->begin();
        if (lSensorInstalled == SENSOR_CO2_BME280 || lSensorInstalled == SENSOR_CO2_BME680) {
            // if CO2-Sensor should measure Temp/Hum, it has to be set on first position in Sensor array
            Sensor::changeSensorOrder(lSensor, 0);
        }
    }
    if (lSensorInstalled == SENSOR_IAQCORE || lSensorInstalled == SENSOR_IAQCORE_BME280 || lSensorInstalled == SENSOR_IAQCORE_SHT3X)
    {
        gSensor = BIT_Voc | BIT_Co2Calc;
        lMeasureTypes = static_cast<MeasureType>(Voc | Co2Calc | Accuracy);
        lSensor = new SensorIAQCore(lMeasureTypes, 0x5A);
        lSensor->begin();
    }
#endif
}
bool ReadSensorValue(MeasureType iMeasureType, float& eValue) {
    return Sensor::measureValue(iMeasureType, eValue);
}

// the entries have the same order as the KOs starting with "Ext"
uint8_t gIsExternalValueValid[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// generic sensor processing
void ProcessSensor(sSensorInfo *cData, getSensorValue fGetSensorValue, MeasureType iMeasureType, float iOffsetFactor, float iValueFactor, uint16_t iParamIndex, uint16_t iKoNumber)
{   
    // we process just a sensor, which is selected in ETS
    if ((gSensor & iMeasureType) != iMeasureType) return;

    bool lForce = cData->sendDelay == 0;
    bool lSend = lForce;

    // process send cycle
    uint32_t lCycle = knx.paramInt(iParamIndex + 1) * 1000;

    // we waited enough, let's send the value
    if (lCycle && delayCheck(cData->sendDelay, lCycle))
        lSend = true;

    // process read cycle
    if (lForce || delayCheck(cData->readDelay, 5000))
    {
        // we waited enough, let's read the sensor
        int32_t lOffset = (int8_t)knx.paramByte(iParamIndex);
        float lValue;
        bool lValid = fGetSensorValue(iMeasureType, lValue);
        if (lValid) {
            // we have now the internal sensor value, we correct it now
            lValue = lValue / iValueFactor;
            lValue += (lOffset / iOffsetFactor);
            // if there are external values to take into account, we do it here
            uint8_t lNumExternalValues = knx.paramByte(iParamIndex + 9) & 3;
            float lDivisor = 0.0f;
            float lDivident = 0.0f;
            float lFactor = 0.0f;
            switch (lNumExternalValues)
            {
                case 2:
                    lFactor = knx.paramByte(iParamIndex + 12) * gIsExternalValueValid[(iKoNumber - LOG_KoTemp) * 2 + 1]; // factor for external value 2
                    lDivident = (float)knx.getGroupObject((iKoNumber - LOG_KoTemp) * 2 + LOG_KoExt2Temp).value(getDPT(VAL_DPT_9)) * lFactor;
                    lDivisor = lFactor;
                case 1:
                    lFactor = knx.paramByte(iParamIndex + 11) * gIsExternalValueValid[(iKoNumber - LOG_KoTemp) * 2]; // factor for external value 1
                    lDivident += (float)knx.getGroupObject((iKoNumber - LOG_KoTemp) * 2 + LOG_KoExt1Temp).value(getDPT(VAL_DPT_9)) * lFactor;
                    lDivisor += lFactor;
                    lFactor = knx.paramByte(iParamIndex + 10); // factor for internal value
                    lDivident += lValue * lFactor;
                    lDivisor += lFactor;
                    if (lDivisor > 0.0f) lValue = lDivident / lDivisor;
                    break;
                default:
                    lDivisor = 1.0f;
                    break;
            }
            if (lDivisor > 0.1f) {
                // smoothing (? glätten ?) of the new value
                // Formel: Value = ValueAlt + (ValueNeu - ValueAlt) / p
                float lValueAlt = (float)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9));
                if (!(lForce && lValueAlt == 0.0f)) {
                    lValue = lValueAlt + (lValue - lValueAlt) / knx.paramByte(iParamIndex + 8);
                }
                // evaluate sending conditions (relative delta / absolute delta)
                if (cData->lastSentValue != NAN) {
                    float lDelta = 100.0f - lValue / cData->lastSentValue * 100.0f;
                    uint8_t lPercent = knx.paramByte(iParamIndex + 7);
                    if (lPercent > 0 && (uint8_t)round(abs(lDelta)) >= lPercent)
                        lSend = true;
                    float lAbsolute = knx.paramWord(iParamIndex + 5) / iOffsetFactor;
                    if (lAbsolute > 0.0f && roundf(abs(lValue - cData->lastSentValue)) >= lAbsolute)
                        lSend = true;
                }
                // we always store the new value in KO, even it it is not sent (to satisfy potential read request)
                knx.getGroupObject(iKoNumber).valueNoSend(lValue, getDPT(VAL_DPT_9));
            }
        } else {
            lSend = false;
        }
        cData->readDelay = millis();
    }
    if (lSend)
    {
        if ((getError() & iMeasureType) == 0) {
            knx.getGroupObject(iKoNumber).objectWritten();
            cData->lastSentValue = (float)knx.getGroupObject(iKoNumber).value(getDPT(VAL_DPT_9));
        }
        cData->sendDelay = millis();
        if (cData->sendDelay == 0) cData->sendDelay = 1;
    }
}

struct sPoint
{
    float x;
    float y;
};

sPoint comfort1[8] = {{17.0f, 88.8f}, {21.4f, 84.1f}, {25.0f, 60.0f}, {27.1f, 30.5f}, {25.9f, 29.5f}, {20.0f, 29.5f}, {17.1f, 48.8f}, {15.9f, 78.8f}};
sPoint comfort2[4] = {{17.5f, 74.7f}, {22.0f, 72.9f}, {24.3f, 37.6f}, {18.9f, 41.8f}};

bool InPolygon(sPoint *iPoly, uint8_t iLen, float iX, float iY)
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

static bool sTempHumValid = false;

// Dewpoint is a vitual sensor and might be implemented on sensor class level, but we implement it here (easier and shorter)
bool CalculateDewValue(MeasureType iMeasureType, float& eValue) {
    float lTemp = knx.getGroupObject(LOG_KoTemp).value(getDPT(VAL_DPT_9));
    float lHum = knx.getGroupObject(LOG_KoHum).value(getDPT(VAL_DPT_9));
    sTempHumValid = sTempHumValid || (lTemp > 0.0f && lHum > 0.0f && !sTempHumValid);
    if (sTempHumValid) {
        float lLogHum = log(lHum / 100.0f);
        eValue = 243.12f * ((17.62f * lTemp) / (243.12f + lTemp) + lLogHum) / ((17.62f * 243.12f) / (243.12f + lTemp) - lLogHum);
    }
    return sTempHumValid;
}

void CalculateComfort(bool iForce = false)
{
    static uint32_t sMillis = 0;
    bool lSend = iForce;
    if (iForce || delayCheck(sMillis, 1000))
    {
        sMillis = millis();
        // do not calculate if underlying measures are corrupt
        if (getError() & (Temperature | Humidity)) return;

        float lTemp = roundf(knx.getGroupObject(LOG_KoTemp).value(getDPT(VAL_DPT_9)));
        float lHum = roundf(knx.getGroupObject(LOG_KoHum).value(getDPT(VAL_DPT_9)));
        sTempHumValid = sTempHumValid || (lTemp > 0.0f && lHum > 0.0f);
        if (sTempHumValid && (knx.paramByte(LOG_Comfort) & 32))
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

void CalculateAccuracy(bool iForce = false)
{
    static uint32_t sMillis = 0;
    bool lSend = iForce;
    if (iForce || delayCheck(sMillis, 60000))
    {
        sMillis = millis();
        // do not calculate if underlying measures are corrupt
        if (getError() & Accuracy) return;

        if (knx.paramByte(LOG_Accuracy) & 8)
        {
            // get accuracy
            float lAccuracyMeasure;
            bool lSuccess = Sensor::measureValue(Accuracy, lAccuracyMeasure);
            if (lSuccess) {
                uint8_t lAccuracy = (uint8_t)lAccuracyMeasure;
                uint8_t lOldAccuracy = (uint8_t)knx.getGroupObject(LOG_KoSensorAccuracy).value(getDPT(VAL_DPT_5001));
                if (lOldAccuracy != lAccuracy)
                    lSend = true;
                if (lSend)
                    knx.getGroupObject(LOG_KoSensorAccuracy).value(lAccuracy, getDPT(VAL_DPT_5001));
            }
        }
    }
}

uint8_t getAirquality(float iCurrent, float* iLimits) {
    uint8_t lResult = 6;
    for (uint8_t i = 0; i < 5; i++)
    {
        if (iCurrent < iLimits[i]) {
            lResult = i + 1;
            break;
        }
    }
    return lResult;
}

void CalculateAirquality(bool iForce = false)
{
    static uint32_t sMillis = 0;
    static float sVocLimits[5] = {51.0f,101.0f,151.0f,201.0f,301.0f};
    static float sCo2Limits[5] = {401.0f,701.0f,1001.0f,1401.0f,2001.0f};

    bool lSend = iForce;
    if (iForce || delayCheck(sMillis, 5000))
    {
        sMillis = millis();
        // do not calculate if underlying measures are corrupt
        if (getError() & (Voc | Co2)) return;
        
        if (knx.paramByte(LOG_Airquality) & 16)
        {
            // do not calculate if underlying measureas are not yet available
            float lValue = 0;

            // get airquality
            uint8_t lAirquality = 6;
            if ((gSensor & BIT_Co2)) {
                // do not calculate if underlying measureas are not yet available
                if (!Sensor::measureValue(Co2, lValue))
                    return;
                lValue = knx.getGroupObject(LOG_KoCo2).value(getDPT(VAL_DPT_9));
                lAirquality = getAirquality(lValue, sCo2Limits);
            } else if ((gSensor & BIT_Voc)) {
                if (!Sensor::measureValue(Voc, lValue))
                    return;
                lValue = knx.getGroupObject(LOG_KoVOC).value(getDPT(VAL_DPT_9));
                lAirquality = getAirquality(lValue, sVocLimits);
            }
            if ((uint8_t)knx.getGroupObject(LOG_KoAirquality).value(getDPT(VAL_DPT_5)) != lAirquality)
                lSend = true;
            if (lSend)
                knx.getGroupObject(LOG_KoAirquality).value(lAirquality, getDPT(VAL_DPT_5));
        }
    }
}

// true solgange der Start des gesamten Moduls verzögert werden soll
bool startupDelay()
{
    return !delayCheck(gRuntimeData.startupDelay, knx.paramInt(LOG_StartupDelay) * 1000);
}

void ProcessSensors(bool iForce = false)
{
    static uint16_t sMeasureType = BIT_Temp;
    static bool sForceComfort = false;
    static bool sForceAirquality = false;
    static bool sForceAccuracy = false;

    if (iForce) {
        // in case we force sending of value, we set all send delays to 0
        gRuntimeData.temp.sendDelay = 0;
        gRuntimeData.hum.sendDelay = 0;
        gRuntimeData.pre.sendDelay = 0;
        gRuntimeData.voc.sendDelay = 0;
        gRuntimeData.co2.sendDelay = 0;
        gRuntimeData.co2b.sendDelay = 0;
        gRuntimeData.dew.sendDelay = 0;
        sForceComfort = true;
        sForceAirquality = true;
        sForceAccuracy = true;
    }
    switch (sMeasureType)
    {
    case BIT_Temp:
        ProcessSensor(&gRuntimeData.temp, ReadSensorValue, Temperature, 10.0f, 1.0f, LOG_TempOffset, LOG_KoTemp);
        break;
    case BIT_Hum:
        ProcessSensor(&gRuntimeData.hum, ReadSensorValue, Humidity, 1.0f, 1.0f, LOG_HumOffset, LOG_KoHum);
        break;
    case BIT_Pre:
        ProcessSensor(&gRuntimeData.pre, ReadSensorValue, Pressure, 1.0f, 100.0f, LOG_PreOffset, LOG_KoPre);
        break;
    case BIT_Voc:
        ProcessSensor(&gRuntimeData.voc, ReadSensorValue, Voc, 1.0f, 1.0f, LOG_VocOffset, LOG_KoVOC);
        break;
    case BIT_Co2:
        ProcessSensor(&gRuntimeData.co2, ReadSensorValue, Co2, 1.0f, 1.0f, LOG_Co2Offset, LOG_KoCo2);
        break;
    case BIT_Co2Calc:
        ProcessSensor(&gRuntimeData.co2b, ReadSensorValue, Co2Calc, 1.0f, 1.0f, LOG_Co2Offset, LOG_KoCo2b);
        break;
    case 0x80:
        if ((gSensor & (BIT_Temp | BIT_Hum)) == (BIT_Temp | BIT_Hum))
            ProcessSensor(&gRuntimeData.dew, CalculateDewValue, static_cast<MeasureType>(Temperature | Humidity), 10.0f, 1.0f, LOG_DewOffset, LOG_KoDewpoint);
        break;
    case 0x100:
        if ((gSensor & (BIT_Temp | BIT_Hum)) == (BIT_Temp | BIT_Hum))
            CalculateComfort(sForceComfort);
        sForceComfort = false;
        break;
    case 0x200:
        if (gSensor & (BIT_Voc | BIT_Co2 | BIT_Co2Calc)) 
            CalculateAirquality(sForceAirquality);
        sForceAirquality = false;
        break;
    case 0x400:
        if (gSensor & BIT_Voc) 
            CalculateAccuracy(sForceAccuracy);
        sForceAccuracy = false;
        break;

    default:
        sMeasureType = 1;
        // error processing
        uint8_t lError = Sensor::getError();
        if (lError != getError()) {
            setError(lError);
            if (knx.paramByte(LOG_Error) & 128)
                sendError();
        }
        break;
    }
    sMeasureType <<= 1;
}

bool processDiagnoseCommand() {
    char* lBuffer = gLogic.getDiagnoseBuffer();
    bool lOutput = false;
    if (lBuffer[0] == 'v') {
        // Command v: retrun fimware version, do not forward this to logic,
        // because it means firmware version of the outermost module
        sprintf(lBuffer, "VER [%d] %d.%d", cFirmwareMajor, cFirmwareMinor, cFirmwareRevision);
        lOutput = true;
    } else {
        // let's check other modules for this command
        lOutput = gLogic.processDiagnoseCommand();
    }
    return lOutput;
}

void ProcessDiagnoseCommand(GroupObject &iKo) {
    // this method is called as soon as iKo is changed
    // an external change is expected
    // because this iKo also is changed within this method, 
    // the method is called again. This might result in 
    // an endless loop. This is prevented by the isCalled pattern.
    static bool sIsCalled = false;
    if (!sIsCalled) {
        sIsCalled = true;
        //diagnose is interactive and reacts on commands
        gLogic.initDiagnose(iKo);
        if (processDiagnoseCommand())
            gLogic.outputDiagnose(iKo);
        sIsCalled = false;
    }
};

void ProcessKoCallback(GroupObject &iKo) {
    // check if we evaluate own KO
    if (iKo.asap() == LOG_KoRequestValues) {
        println("Request values called");
        // print("KO-Value is ");
        // println((bool)iKo.value(getDpt(VAL_DPT_1)));
        if ((bool)iKo.value(getDPT(VAL_DPT_1)))
            gRuntimeData.forceSensorRead = true;
    } else if (iKo.asap() == LOG_KoDiagnose) {
        ProcessDiagnoseCommand(iKo);
    } else if (iKo.asap() >= LOG_KoExt1Temp && iKo.asap() <= LOG_KoExt2Co2) {
        // as soon as we receive any external sensor value, we mark this in our validity map
        gIsExternalValueValid[iKo.asap() - LOG_KoExt1Temp] = 1;
    } else {
        // else dispatch to logicmodule
        gLogic.processInputKo(iKo);
    }
}

void ProcessInterrupt() {
    if (gRuntimeData.saveInterruptTimestamp) {
        printDebug("Sensormodul: SAVE-Interrupt processing started after %lu ms\n", millis() - gRuntimeData.saveInterruptTimestamp);
        gRuntimeData.saveInterruptTimestamp = millis();
        // for the moment, we send only an Info on error object in case of an save interrumpt
        uint16_t lError = getError();
        setError(lError | 128);
        sendError();
        // switch off all energy intensive hardware to gain time for EEPROM write
        savePower();
        // call according logic interrupt handler
        gLogic.processInterrupt(true);
        Sensor::saveState();
        printDebug("Sensormodul: SAVE-Interrupt processing duration was %lu ms\n", millis() - gRuntimeData.saveInterruptTimestamp);
        // in case, SaveInterrupt was a false positive
        // we restore power and I2C-Bus
        // Wire.end();
        // wait another 200 ms
        delay(200);
        restorePower();
        delay(100);
        // Wire.begin();
        // Sensor::restartSensors();
        gRuntimeData.saveInterruptTimestamp = 0;
    }
}


void appLoop()
{

    if (!knx.configured())
        return;

    // handle KNX stuff
    if (startupDelay())
        return;

    gRuntimeData.isRunning = true;
    ProcessInterrupt();

    // at this point startup-delay is done
    // we process heartbeat
    ProcessHeartbeat();
    ProcessReadRequests();
    gLogic.loop();

    // at Startup, we want to send all values immediately
    ProcessSensors(gRuntimeData.forceSensorRead);
    gRuntimeData.forceSensorRead = false;

    Sensor::sensorLoop();
}

// handle interrupt from save pin
void onSafePinInterruptHandler() {
    gRuntimeData.saveInterruptTimestamp = millis();
    gLogic.onSafePinInterruptHandler();
}

void beforeRestartHandler() {
    printDebug("before Restart called\n");
    Sensor::saveState();
    gLogic.onBeforeRestartHandler();
    // we try get a clean state on I2C bus
    Wire.end();
}

void beforeTableUnloadHandler(TableObject& iTableObject, LoadState& iNewState) {
    static uint32_t sLastCalled = 0;
    printDebug("Table changed called with state %d\n", iNewState);
    
    if (iNewState == 0) {
        printDebug("Table unload called\n");
        if (sLastCalled == 0 || delayCheck(sLastCalled, 10000)) {
            Sensor::saveState();
            gLogic.onBeforeTableUnloadHandler(iTableObject, iNewState);
            sLastCalled = millis();
        }
    }
}

void appSetup(uint8_t iSavePin)
{

    // try to get rid of occasional I2C lock...
    // savePower();
    digitalWrite(PROG_LED_PIN, HIGH);
    digitalWrite(LED_YELLOW_PIN, HIGH);
    // delay(1000);
    // restorePower();
    // check hardware availability
    boardCheck();
    digitalWrite(PROG_LED_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
    // The module prints its firmware version to the console
    printDebug("Firmware-Version [%d] %d.%d\n", cFirmwareMajor, cFirmwareMinor, cFirmwareRevision);

    if (knx.configured())
    {
        // 5 bit major, 5 bit minor, 6 bit revision
        knx.bau().deviceObject().version(cFirmwareMajor << 11 | cFirmwareMinor << 6 | cFirmwareRevision);
        // gSensor = (knx.paramByte(LOG_SensorDevice));
        gRuntimeData.startupDelay = millis();
        gRuntimeData.heartbeatDelay = 0;
        // GroupObject &lKoRequestValues = knx.getGroupObject(LOG_KoRequestValues);
        if (GroupObject::classCallback() == 0) GroupObject::classCallback(ProcessKoCallback);
        if (knx.getBeforeRestartCallback() == 0) knx.addBeforeRestartCallback(beforeRestartHandler);
        if (TableObject::getBeforeTableUnloadCallback() == 0) TableObject::addBeforeTableUnloadCallback(beforeTableUnloadHandler);
        StartSensor();
        if (iSavePin) 
            attachInterrupt(digitalPinToInterrupt(iSavePin), onSafePinInterruptHandler, FALLING);
        gLogic.setup(false);
    }
}