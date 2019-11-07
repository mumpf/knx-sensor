#pragma once
#include <ClosedCube_HDC1080.h>
#include "Sensor.h"

class SensorHDC1080 : public Sensor, protected ClosedCube_HDC1080
{

protected:
    double measureValue(MeasureType iMeasureType) override;

public:
    SensorHDC1080(uint8_t iMeasureTypes, uint8_t iAddress);
    virtual ~SensorHDC1080() {}
    bool begin() override; 
};
