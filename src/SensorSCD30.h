#pragma once
#include <SparkFun_SCD30_Arduino_Library.h>
#include "Sensor.h"

class SensorSCD30 : public Sensor, protected SCD30
{

protected:
    double measureValue(MeasureType iMeasureType) override;

public:
    SensorSCD30(uint8_t iMeasureTypes, uint8_t iAddress);
    virtual ~SensorSCD30() {}
    bool begin() override; 
};
