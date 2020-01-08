#pragma once
#include <knx/bits.h>
#include "../../knx-logic/src/Board.h"

#define BIT_1WIRE 1
#define BIT_Temp 2
#define BIT_Hum 4
#define BIT_Pre 8
#define BIT_Voc 16
#define BIT_Co2 32
#define BIT_RESERVE 64
#define BIT_LOGIC 128

enum SensorState {
    Off,
    Wakeup,
    Calibrate,
    Finalize,
    Running
};

enum MeasureType {
    OneWire = 1,
    Temperature = 2,
    Humidity = 4,
    Pressure = 8,
    Voc = 16,
    Co2 = 32,
    Accuracy = 64,
    Reserved = 128 // temporary: co2 from voc
};

class Sensor
{
  private:
    static Sensor* sSensors[2];
    static uint8_t sNumSensors;
    uint8_t gMeasureTypes;

  protected:
    // Sensor();
    uint8_t gAddress;
    SensorState gSensorState = Off;
    uint32_t gSensorStateDelay = 0;

    bool CheckSensorConnection();
    virtual double measureValue(MeasureType iMeasureType) = 0; //pure
    virtual void sensorLoopInternal();
    virtual void sensorSaveState();
    // non blocking restart approach for a sensor
    void restartSensor();

  public:
    Sensor(uint8_t iMeasureTypes, uint8_t iAddress);
    virtual ~Sensor() {}

    // static 
    static void sensorLoop();
    static bool measureValue(MeasureType iMeasureType, double& eValue);
    static uint8_t getError();
    static void saveState();
    static void restartSensors();

    virtual bool begin(); // first initialization, may be blocking, should be called druing setup(), not during loop()
};
