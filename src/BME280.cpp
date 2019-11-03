#include <BME280.h>

BME280::BME280()
    : _BME280()
{
};

/*!
 *   @brief  Initialise sensor with given parameters / settings, skips all delay functions, expects correct external call sequence
 *   @returns true on success, false otherwise
 */
bool BME280::initWakeup()
{
    // init I2C or SPI sensor interface
    if (_cs == -1)
    {
        // I2C
        _wire->begin();
    }
    else
    {
        digitalWrite(_cs, HIGH);
        pinMode(_cs, OUTPUT);
        if (_sck == -1)
        {
            // hardware SPI
            _spi->begin();
        }
        else
        {
            // software SPI
            pinMode(_sck, OUTPUT);
            pinMode(_mosi, OUTPUT);
            pinMode(_miso, INPUT);
        }
    }

    // check if sensor, i.e. the chip ID is correct
    _sensorID = read8(BME280_REGISTER_CHIPID);
    if (_sensorID != 0x60)
        return false;

    // reset the device using soft-reset
    // this makes sure the IIR is off, etc.
    write8(BME280_REGISTER_SOFTRESET, 0xB6);
    return true;
}

bool BME280::initFinalize() {
    // // wait for chip to wake up.
    // delay(300);

    // // if chip is still reading calibration, delay
    // while (isReadingCalibration())
    //     delay(100);

    readCoefficients(); // read trimming parameters, see DS 4.2.2

    setSampling(); // use defaults

    // delay(100);

    return true;
}

/*!
 * @brief implements a state engine to restart the sensor without delays
 */
void BME280::loop() {
    switch (_isRestarting)
    {
    case Wakeup:
        if (initWakeup()) {
            _millisRestarting = millis();
            _isRestarting = Finalize;
        }
        break;
    case Finalize:
        if (_millisRestarting + 100 > millis()) {
            if (!isReadingCalibration()) {
                initFinalize();
                _isRestarting = Finish;
            }
            _millisRestarting = millis();
        }
        break;
    case Finish:
        if (_millisRestarting + 100 > millis()) _isRestarting = Idle;
        break;
    default:
        // do nothing
        break;
    }
}
