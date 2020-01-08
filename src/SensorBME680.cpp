#include <knx/bits.h>
#include "SensorBME680.h"
#include "bsec/bme680/bme680.h"
#include "../../knx-logic/src/Board.h"

#define STATE_SAVE_PERIOD  UINT32_C(360 * 60 * 1000) // 360 minutes - 4 times a day
#define EEPROM_BME680_START_ADDRESS 0xC80


SensorBME680::SensorBME680(uint8_t iMeasureTypes, uint8_t iAddress, bme680_delay_fptr_t iDelayCallback)
    : Sensor(iMeasureTypes, iAddress), Bsec(), gDelayCallback(iDelayCallback) {};

bsec_virtual_sensor_t SensorBME680::sensorList[] = {
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_STABILIZATION_STATUS,
    BSEC_OUTPUT_RUN_IN_STATUS,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    BSEC_OUTPUT_COMPENSATED_GAS,
    BSEC_OUTPUT_GAS_PERCENTAGE
};

// from 33v_3s_4d example
uint8_t SensorBME680::bsec_config_iaq[454] =
       {4, 7, 4, 1, 61, 0, 0, 0, 0, 0, 0, 0, 174, 1, 0, 0, 48, 0, 1, 0, 0, 192, 168, 71, 64, 49, 119, 76, 0, 0, 225, 68, 137, 65, 0, 63, 205, 204, 204, 62, 0, 0, 64, 63, 205, 204, 204, 62, 0, 0, 0, 0, 216, 85, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 28, 0, 2, 0, 0, 244, 1, 225, 0, 25, 0, 0, 128, 64, 0, 0, 32, 65, 144, 1, 0, 0, 112, 65, 0, 0, 0, 63, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 9, 0, 5, 0, 0, 0, 0, 0, 1, 88, 0, 9, 0, 229, 208, 34, 62, 0, 0, 0, 0, 0, 0, 0, 0, 218, 27, 156, 62, 225, 11, 67, 64, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 94, 75, 72, 189, 93, 254, 159, 64, 66, 62, 160, 191, 0, 0, 0, 0, 0, 0, 0, 0, 33, 31, 180, 190, 138, 176, 97, 64, 65, 241, 99, 190, 0, 0, 0, 0, 0, 0, 0, 0, 167, 121, 71, 61, 165, 189, 41, 192, 184, 30, 189, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 229, 0, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 0, 0, 0, 0, 138, 80, 0, 0};
    // {3, 7, 4, 1, 61, 0, 0, 0, 0, 0, 0, 0, 174, 1, 0, 0, 48, 0, 1, 0, 0, 168,  19, 73, 64, 49, 119, 76, 0, 0, 225, 68, 137, 65, 0, 63, 205, 204, 204, 62, 0, 0, 64, 63, 205, 204, 204, 62, 0, 0, 0, 0,   0, 80, 5,  95, 0, 0, 0, 0, 0, 0, 0, 0, 28, 0, 2, 0, 0, 244, 1, 225, 0, 25, 0, 0, 128, 64, 0, 0, 32, 65, 144, 1, 0, 0, 112, 65, 0, 0, 0, 63, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 9, 0, 5, 0, 0, 0, 0, 0, 1, 88, 0, 9, 0, 229, 208, 34, 62, 0, 0, 0, 0, 0, 0, 0, 0, 218, 27, 156, 62, 225, 11, 67, 64, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 94, 75, 72, 189, 93, 254, 159, 64, 66, 62, 160, 191, 0, 0, 0, 0, 0, 0, 0, 0, 33, 31, 180, 190, 138, 176, 97, 64, 65, 241, 99, 190, 0, 0, 0, 0, 0, 0, 0, 0, 167, 121, 71, 61, 165, 189, 41, 192, 184, 30, 189, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 229, 0, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 0, 0, 0, 0, 222, 38, 0, 0};

// EEPROM memory start id
uint8_t SensorBME680::sMagicWord[] = {0xCA, 0xFE, 0x3D, 0x76};

void SensorBME680::sensorLoopInternal() {
    if (gSensorState == Running) {
        if (Bsec::run()) {
            sensorUpdateState();
            checkIaqSensorStatus();
        }
    }
}

double SensorBME680::measureValue(MeasureType iMeasureType) {
    // run() uses gDelayCallback to call timing critical methods (knx communication, logic evaluation)
    // in cases where measurement needs longer time
    // if (run()) {
    //     sensorUpdateState();
    // } else {
    //     checkIaqSensorStatus();
    // };
    switch (iMeasureType)
    {
    case Temperature:
        return Bsec::temperature;
        break;
    case Humidity:
        return Bsec::humidity;
        break;
    case Pressure:
        return Bsec::pressure;
        break;
    case Voc:
        return Bsec::iaq;
        break;
    case Co2:
        return Bsec::co2Equivalent;
        break;
    case Accuracy:
        return (Bsec::iaqAccuracy / 3.0) * 100.0 ;
        break;
    default:
        break;
    }
    return -1000.0;
}

bool SensorBME680::begin() {
    print("Starting sensor BME680... ");
    Bsec::begin(BME680_I2C_ADDR_PRIMARY, Wire, gDelayCallback);
    bool lResult = checkIaqSensorStatus();
    if (lResult) {
        Bsec::setConfig(bsec_config_iaq);
        lResult = checkIaqSensorStatus();
    }
    if (lResult) {
        Bsec::updateSubscription(sensorList, sizeof(sensorList)/sizeof(bsec_virtual_sensor_t), BSEC_SAMPLE_RATE_LP);
        lResult = checkIaqSensorStatus();
    }
    if (lResult) {
        sensorLoadState();
        lResult = checkIaqSensorStatus();
    }
    if (lResult)
        lResult = Sensor::begin();
    printResult(lResult);
    return lResult;
}

bool SensorBME680::checkIaqSensorStatus(void)
{
    if (Bsec::status < BSEC_OK)
    {
        printf("BSEC error code : %d", Bsec::status);
        return false;
        // fatalError(-iaqSensor.status, "BSEC error code");
    }
    else if (Bsec::status > BSEC_OK)
        printf("BSEC warning code : %d", Bsec::status);

    if (Bsec::bme680Status < BME680_OK)
    {
        printf("BME680 error code : %d", Bsec::bme680Status);
        return false;
        // fatalError(-iaqSensor.bme680Status, "BME680 error code");
    }
    else if (Bsec::bme680Status > BME680_OK)
        printf("BME680 warning code : %d", Bsec::bme680Status);

    return true;
}

void SensorBME680::sensorLoadState()
{
    uint8_t buffer[144]; //[BSEC_MAX_STATE_BLOB_SIZE];
    // Existing state in EEPROM
    println("Reading BME680 state from EEPROM");
    prepareReadEEPROM(EEPROM_BME680_START_ADDRESS, 144);
    if (Wire.available()) Wire.readBytes(buffer, 144);

    for (uint8_t i = 0; i < 144; i+=16)
        printHex("<-- ", buffer + i, 16);
    bool lCheck = true;
    for (uint8_t lIndex = 0; lIndex < 4 && lCheck; lIndex++)
        lCheck = (buffer[lIndex] == sMagicWord[lIndex]);
    
    if (lCheck) {
        Bsec::setState(buffer + 4);
        checkIaqSensorStatus();
    }
}

// We store sensor data in EEPROM stating at page 100 (100 * 32 = 3200 = 0xC80).
// We write in 16 Byte chunks, a maximum of 139 bytes, means 139/16 = 9 chunks (which is in fact 144 Bytes).
// Timing is 9 * 5 ms = 45 ms write time
void SensorBME680::sensorSaveState()
{
    // buffer gets freed inside knx object after saved
    uint8_t buffer[144] = {0}; //[BSEC_MAX_STATE_BLOB_SIZE];
    for (uint8_t lIndex = 0; lIndex < 4; lIndex++)
        buffer[lIndex] = sMagicWord[lIndex];

    Bsec::getState(buffer + 4);
    bool lCheck = checkIaqSensorStatus();
    if (lCheck) { 
    println("Writing BME680 state to EEPROM");

    for (uint8_t lCount = 0; lCount < 144; lCount += 16)
        {
            beginPageEEPROM(EEPROM_BME680_START_ADDRESS + lCount);
            Wire.write(buffer + lCount, 16);
            endPageEEPROM();
            printHex("--> ", buffer + lCount, 16);
        }
    }
}

void SensorBME680::sensorUpdateState(void)
{
    // we save the sensor state each time accuracy is raised 
    // and 4 times a day if accuracy is 3 (this might be senseless, if we save with each restart)
    if ((Bsec::iaqAccuracy > gLastAccuracy) || (Bsec::iaqAccuracy >= 3 && delayCheck(stateUpdateTimer, STATE_SAVE_PERIOD)))
    {
        sensorSaveState();
        stateUpdateTimer = millis();
    }
    gLastAccuracy = Bsec::iaqAccuracy;
}
