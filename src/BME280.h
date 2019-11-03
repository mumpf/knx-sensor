#pragma once
#include <Adafruit_BME280.h>

enum RestartState {
    Idle,
    Wakeup,
    Finalize,
    Finish
};

class BME280 : protected Adafruit_BME280
{
private:
    Adafruit_BME280 _BME280;
    RestartState _isRestarting = Idle;
    uint32_t _millisRestarting;
    bool initWakeup();
    bool initFinalize();

public:
    BME280();
    void loop();
    bool isInitialized();
    void wakeup();
};
