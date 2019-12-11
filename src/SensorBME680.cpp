#include <knx/bits.h>
#include "SensorBME680.h"
#include "bsec/bme680/bme680.h"
#include "../../knx-logic/src/Board.h"

#define STATE_SAVE_PERIOD  UINT32_C(360 * 60 * 1000) // 360 minutes - 4 times a day

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

uint8_t SensorBME680::gMagicWord[] = {0xCA, 0xFE, 0x3D, 0x74};

double SensorBME680::measureValue(MeasureType iMeasureType) {
    // run() uses gDelayCallback to call timing critical methods (knx communication, logic evaluation)
    // in cases where measurement needs longer time
    run();
    updateState();
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
    case Accuracy:
        return (Bsec::iaqAccuracy / 3) * 100.0 ;
        break;
    default:
        break;
    }
    return -1000.0;
}

bool SensorBME680::begin() {
    Bsec::begin(BME680_I2C_ADDR_PRIMARY, Wire, gDelayCallback);
    bool lResult = checkIaqSensorStatus();
    if (lResult) {
        Bsec::updateSubscription(sensorList, sizeof(sensorList)/sizeof(bsec_virtual_sensor_t), BSEC_SAMPLE_RATE_LP);
        lResult = checkIaqSensorStatus();
    }
    if (lResult) {
        loadBme680State();
        lResult = checkIaqSensorStatus();
    }
    if (lResult)
        lResult = Sensor::begin();
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

#define EEPROM_BME680_START_ADDRESS 0xC80
#define EEPROM_BLOB_SIZE BSEC_MAX_STATE_BLOB_SIZE + (BSEC_MAX_STATE_BLOB_SIZE % 16)

void SensorBME680::loadBme680State()
{
    uint8_t buffer[144]; //[BSEC_MAX_STATE_BLOB_SIZE];
    // Existing state in EEPROM
    println("Reading state from EEPROM");
    prepareReadEEPROM(EEPROM_BME680_START_ADDRESS, BSEC_MAX_STATE_BLOB_SIZE);
    if (Wire.available()) Wire.readBytes(buffer, BSEC_MAX_STATE_BLOB_SIZE);

    // for (uint8_t i = 0; i < BSEC_MAX_STATE_BLOB_SIZE; i++)
    // {
    //     SerialUSB.println(buffer[i], HEX);
    // }
    bool lCheck = true;
    for (uint8_t lIndex = 0; lIndex < 4 && lCheck; lIndex++)
        lCheck = (buffer[lIndex] == gMagicWord[lIndex]);
    
    if (lCheck) {
        Bsec::setState(buffer + 4);
        checkIaqSensorStatus();
    }
}

// We store sensor data in EEPROM stating at page 100 (100 * 32 = 3200 = 0xC80).
// We write in 16 Byte chunks, a maximum of 139 bytes, means 139/16 = 9 chunks (which is in fact 144 Bytes).
// Timing is 9 * 5 ms = 45 ms write time
void SensorBME680::saveBme680State(bool iIsInterrupt)
{
    // buffer gets freed inside knx object after saved
    uint8_t buffer[144] = {0}; //[BSEC_MAX_STATE_BLOB_SIZE];
    for (uint8_t lIndex = 0; lIndex < 4; lIndex++)
        buffer[lIndex] = gMagicWord[lIndex];

    Bsec::getState(buffer + 4);
    if (!iIsInterrupt) checkIaqSensorStatus();
    println("Writing state to EEPROM");

    for (uint8_t lCount = 0; lCount < 144; lCount += 16)
    {
        beginPageEEPROM(EEPROM_BME680_START_ADDRESS + lCount);
        Wire.write(buffer + lCount, 16);
        endPageEEPROM(iIsInterrupt);
    }
    
    // for (uint8_t i = 0; i < BSEC_MAX_STATE_BLOB_SIZE; i++)
    // {
    //     println(buffer[i], HEX);
    // }
}

void SensorBME680::updateState(void)
{
    if ((stateUpdateTimer == 0 && Bsec::iaqAccuracy >= 3) || delayCheck(stateUpdateTimer, STATE_SAVE_PERIOD))
    {
        saveBme680State(false);
        stateUpdateTimer = millis();
    }
}
