#include <Wire.h>
#include "Sensor.h"

// static
uint8_t Sensor::sNumSensors = 0;
Sensor* Sensor::sSensors[2];

Sensor::Sensor(uint8_t iMeasureTypes, uint8_t iAddress)
{
    if (sNumSensors >= 2) {
        println("Sensor::Sensor() - Currently only 2 (Hardware)Sensors are supported");
        //fatal error handling
        return;
    }
    gMeasureTypes = iMeasureTypes;
    gAddress = iAddress;
    sSensors[sNumSensors++] = this;
};

// static
void Sensor::sensorLoop() {
    for (uint8_t lCounter = 0; lCounter < sNumSensors; lCounter++)
        sSensors[lCounter]->sensorLoopInternal();
    }

// static
void Sensor::restartSensors() {
    for (uint8_t lCounter = 0; lCounter < sNumSensors; lCounter++)
        sSensors[lCounter]->restartSensor();
}

void Sensor::restartSensor() {
    gSensorStateDelay = 0;
    gSensorState = Wakeup;
}

bool Sensor::CheckSensorConnection()
{
    bool lResult = false;
    if (gSensorState == Running) {
        // ceck for I2C ack
        Wire.beginTransmission(gAddress);
        lResult = (Wire.endTransmission() == 0);
        if (!lResult)
            restartSensor();
    }
    return lResult;
}

void Sensor::sensorLoopInternal() {
    switch (gSensorState)
    {
    case Wakeup:
        // try immediately to start the sensor, then every second
        if (gSensorStateDelay == 0 || millis() > gSensorStateDelay + 1000) {
            if (begin()) gSensorState = Finalize;
            gSensorStateDelay = millis();
        }
        break;
    case Finalize:
        // give the sensor 100 ms before querying starts
        if (millis() > gSensorStateDelay + 100) gSensorState = Running;
        break;
    default:
        gSensorStateDelay = 0;
        break;
    }
}

bool Sensor::begin() {
    gSensorState = Running;
    return CheckSensorConnection();
}

// should be overridden, if there is a state to save before power failure
void Sensor::sensorSaveState(bool iIsInterrupt) {};

// static
void Sensor::saveState(bool iIsInterrupt) {
    // dispatch the call to all sensors
    for (uint8_t lCounter = 0; lCounter < sNumSensors; lCounter++)
        sSensors[lCounter]->sensorSaveState(iIsInterrupt);
}

// static
bool Sensor::measureValue(MeasureType iMeasureType, double& eValue) {
    bool lResult = false;
    for (uint8_t lCounter = 0; lCounter < sNumSensors; lCounter++)
    {
        if (sSensors[lCounter]->gMeasureTypes & iMeasureType) {
            lResult = sSensors[lCounter]->CheckSensorConnection();
            if (lResult) eValue = sSensors[lCounter]->measureValue(iMeasureType);
            break;
        }
    }
    return lResult;
}

//static
uint8_t Sensor::getError() {
    uint8_t lResult = 0;
    for (uint8_t lCounter = 0; lCounter < sNumSensors; lCounter++)
    {
        if (sSensors[lCounter]->gSensorState != Running) {
            lResult |= sSensors[lCounter]->gMeasureTypes;
        }
    }
    return lResult;
}