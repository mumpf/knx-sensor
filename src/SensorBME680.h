#pragma once
#include "bsec/bsec.h"
#include "Sensor.h"

class SensorBME680 : public Sensor, protected Bsec
{

protected:
    double measureValue(MeasureType iMeasureType) override;
    bool checkIaqSensorStatus(void);
    void saveBme680State(bool iIsInterrupt);
    void loadBme680State();
    void updateState();
    uint32_t stateUpdateTimer = 0;
    static bsec_virtual_sensor_t sensorList[];
    bme680_delay_fptr_t gDelayCallback = 0;

  public:
    SensorBME680(uint8_t iMeasureTypes, uint8_t iAddress, bme680_delay_fptr_t iDelayCallback);
    virtual ~SensorBME680() {}
    bool begin() override;

  private:
    static uint8_t gMagicWord[];

};
