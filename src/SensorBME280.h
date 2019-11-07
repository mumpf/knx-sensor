#pragma once
#include <Adafruit_BME280.h>
#include "Sensor.h"

class SensorBME280 : public Sensor, protected Adafruit_BME280
{

protected:
    double measureValue(MeasureType iMeasureType) override;
    void sensorLoopInternal() override;
    bool initWakeup();
    bool initFinalize();

public:
    SensorBME280(uint8_t iMeasureTypes, uint8_t iAddress);
    virtual ~SensorBME280() {}
    bool begin() override; 
};
