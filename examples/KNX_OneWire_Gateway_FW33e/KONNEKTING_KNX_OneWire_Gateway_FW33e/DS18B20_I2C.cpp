#include <Wire.h>
#include <arduino.h>
#include <math.h>
#include <DebugUtil.h>

#include "DS18B20_I2C.h"

//#define DebugInfo
//#define DebugInfoTemp


I2C_DS18B20::I2C_DS18B20()
{
  // Address is determined by two pins on the DS2482 AD1/AD0
  // Pass 0b00, 0b01, 0b10 or 0b11
  //mAddress = 0x18;
  //mError = 0;
  //Wire.begin();
};

void I2C_DS18B20::init(DS2482_OneWire *ow, uint8_t *address_DS18B20, bool isactive, float diff_T, bool Alarm1, float Alarm1_HT, float Alarm1_TT, bool Alarm2, float Alarm2_HT, float Alarm2_TT ) {
  _ow = ow;
  _address_DS18B20 = address_DS18B20;
  _isActive = isactive;

  //alarm 1& 2
  _alarm1 = Alarm1;
  _alarm1_HT = Alarm1_HT;
  _alarm1_TT = Alarm1_TT;
  _alarm2 = Alarm2;
  _alarm2_HT = Alarm2_HT;
  _alarm2_TT = Alarm2_TT;

  _diff_T = (diff_T / 10.0);
  if (diff_T != 0)
    is_diff_T_active = true;



  if (!parasite && readPowerSupply(_address_DS18B20)) parasite = true;
  bitResolution = max(bitResolution, getResolution(_address_DS18B20));
}


void I2C_DS18B20::setActive(bool state) {
  _isActive = state;
}

bool I2C_DS18B20::getisActive() {
  return _isActive;
}


float I2C_DS18B20::getTemp() {
  return temp - calValueT;
}

bool  I2C_DS18B20::isSend_Temp() {
  return is_diff_T_active;
}


bool  I2C_DS18B20::doSend_Temp() {
  return _send_Temp;
}

void  I2C_DS18B20::clearSend_Temp() {
  _send_Temp = false;
}

bool I2C_DS18B20::getAlarm1() {
  return _alarm1;
}

bool I2C_DS18B20::getAlarm2() {
  return _alarm2;
}

bool I2C_DS18B20::getAlarm1_HT() {
  return _isAlarm1_HT;
}

bool I2C_DS18B20::getAlarm1_TT() {
  return _isAlarm1_TT;
}

bool I2C_DS18B20::getAlarm2_HT() {
  return _isAlarm2_HT;
}

bool I2C_DS18B20::getAlarm2_TT() {
  return _isAlarm2_TT;
}

boolean I2C_DS18B20::startConversion_Temp() {

  _ow->reset();
  _ow->select(_address_DS18B20);
  _ow->write(0x44, 1);        // Wandlung mit aktivierter parasitärer Versorgung starten
  return true;
}



boolean I2C_DS18B20::update_Temp() {

  present =  _ow->reset();
  _ow->select(_address_DS18B20);

  _ow->write(0xBE);         // Scratchpad auslesen
#ifdef DebugInfoTemp
  Debug.print(F("Data = %d"), present);
  Debug.println(" ");
#endif

  for ( i = 0; i < 9; i++) {           // Wir brauchen 9 Byte
    data[i] =  _ow->read();
#ifdef DebugInfoTemp
    Debug.print(F("%02x "), data[i]);

#endif
  }
#ifdef DebugInfoTemp
  Debug.println(" ");
  Debug.print("CRC = ");
  Debug.println(F("%02x"), DS2482_OneWire::crc8(data, 8));
#endif
  byte cfg = (data[4] & 0x60);
#ifdef DebugInfoTemp
  Debug.print("cfg = ");
  Debug.println(F("%02x"), cfg);

#endif
  raw = (data[1] << 8) | data[0];

  if (cfg == 0x00) raw = raw & ~7;      // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  else if (cfg == 0x60) raw = raw;      // 12 bit res, 750 ms



  //speichert ersten Wert in OLD um später damit den aktuellen Wert vergleichen zu können.
  if (temp_init == false) {
    temp_old = (float)raw / 16.0;
    temp = temp_old;
    temp_init = true;
  }
  else {
    temp = (float)raw / 16.0;
    //Wertänderung
    if (is_diff_T_active) {
      if (abs(temp - temp_old)  > _diff_T) {
        _send_Temp = true;
      }
      temp_old = temp;
    }
    //Alarm
    if (temp >= _alarm1_HT)
      _isAlarm1_HT = true;
    else
      _isAlarm1_HT = false;
    if (temp <= _alarm1_TT)
      _isAlarm1_TT = true;
    else
      _isAlarm1_TT = false;

    if (temp >= _alarm2_HT)
      _isAlarm2_HT = true;
    else
      _isAlarm2_HT = false;
    if (temp <= _alarm2_TT)
      _isAlarm2_TT = true;
    else
      _isAlarm2_TT = false;
  }


#ifdef DebugInfoTemp
  Debug.println(F("Temp = %0.1f°C"), temp);
#endif
}

// reads the device's power requirements
bool I2C_DS18B20::readPowerSupply(const uint8_t* deviceAddress)
{
  bool ret = false;
  _ow->reset();
  _ow->select(deviceAddress);
  _ow->write(READPOWERSUPPLY);
  if (_ow->read_bit() == 0) ret = true;
  _ow->reset();
  return ret;
}


// returns true if the bus requires parasite power
bool I2C_DS18B20::isParasitePowerMode(void)
{
  return parasite;
}


// attempt to determine if the device at the given address is connected to the bus
bool I2C_DS18B20::isConnected()
{
  ScratchPad scratchPad;
  return isConnected(_address_DS18B20, scratchPad);
}


// attempt to determine if the device at the given address is connected to the bus
bool I2C_DS18B20::isConnected(const uint8_t* deviceAddress)
{
  ScratchPad scratchPad;
  return isConnected(deviceAddress, scratchPad);
}

// attempt to determine if the device at the given address is connected to the bus
// also allows for updating the read scratchpad
bool I2C_DS18B20::isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  readScratchPad(deviceAddress, scratchPad);
  return (_ow->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC]);
}


// returns the global resolution
uint8_t I2C_DS18B20::getResolution()
{
  getResolution(_address_DS18B20);
}


// returns the current resolution of the device, 9-12
// returns 0 if device not found
uint8_t I2C_DS18B20::getResolution(const uint8_t* deviceAddress)
{
  // this model has a fixed resolution of 9 bits but getTemp calculates
  // a full 12 bits resolution and we need 750ms convert time
  if (deviceAddress[0] == DS18S20MODEL) return 12;

  ScratchPad scratchPad;
  if (isConnected(deviceAddress, scratchPad))
  {
    switch (scratchPad[CONFIGURATION])
    {
      case TEMP_12_BIT:
        return 12;

      case TEMP_11_BIT:
        return 11;

      case TEMP_10_BIT:
        return 10;

      case TEMP_9_BIT:
        return 9;
    }
  }
  return 0;
}



// set resolution of all devices to 9, 10, 11, or 12 bits
// if new resolution is out of range, it is constrained.
bool I2C_DS18B20::setResolution(uint8_t newResolution)
{
  bitResolution = constrain(newResolution, 9, 12);

  ScratchPad scratchPad;
  if (isConnected(_address_DS18B20, scratchPad))
  {

    // DS18S20 has a fixed 9-bit resolution
    if (_address_DS18B20[0] != DS18S20MODEL)
    {

      switch (bitResolution)
      {
        case 12:
          scratchPad[CONFIGURATION] = TEMP_12_BIT;
          break;
        case 11:
          scratchPad[CONFIGURATION] = TEMP_11_BIT;
          break;
        case 10:
          scratchPad[CONFIGURATION] = TEMP_10_BIT;
          break;
        case 9:
        default:
          scratchPad[CONFIGURATION] = TEMP_9_BIT;
          break;
      }
      writeScratchPad(_address_DS18B20, scratchPad);
    }
    return true;  // new value set
  }
  return false;
}


// writes device's scratch pad
void I2C_DS18B20::writeScratchPad(const uint8_t* deviceAddress, const uint8_t* scratchPad)
{
  _ow->reset();
  _ow->select(deviceAddress);
  _ow->write(WRITESCRATCH);
  _ow->write(scratchPad[HIGH_ALARM_TEMP]); // high alarm temp
  _ow->write(scratchPad[LOW_ALARM_TEMP]); // low alarm temp
  // DS18S20 does not use the configuration register
  if (deviceAddress[0] != DS18S20MODEL) _ow->write(scratchPad[CONFIGURATION]); // configuration
  _ow->reset();
  // save the newly written values to eeprom
  _ow->write(COPYSCRATCH, parasite);
  if (parasite) delay(10); // 10ms delay
  _ow->reset();
}



// read device's scratch pad
void I2C_DS18B20::readScratchPad(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  // send the command
  _ow->reset();
  _ow->select(_address_DS18B20);
  _ow->write(READSCRATCH);      // 0xBE  // Read EEPROM

  // TODO => collect all comments &  use simple loop
  // byte 0: temperature LSB
  // byte 1: temperature MSB
  // byte 2: high alarm temp
  // byte 3: low alarm temp
  // byte 4: DS18S20: store for crc
  //         DS18B20 & DS1822: configuration register
  // byte 5: internal use & crc
  // byte 6: DS18S20: COUNT_REMAIN
  //         DS18B20 & DS1822: store for crc
  // byte 7: DS18S20: COUNT_PER_C
  //         DS18B20 & DS1822: store for crc
  // byte 8: SCRATCHPAD_CRC
  //
  // for(int i=0; i<9; i++)
  // {
  //   scratchPad[i] = _wire->read();
  // }


  // read the response

  // byte 0: temperature LSB
  scratchPad[TEMP_LSB] = _ow->read();

  // byte 1: temperature MSB
  scratchPad[TEMP_MSB] = _ow->read();

  // byte 2: high alarm temp
  scratchPad[HIGH_ALARM_TEMP] = _ow->read();

  // byte 3: low alarm temp
  scratchPad[LOW_ALARM_TEMP] = _ow->read();

  // byte 4:
  // DS18S20: store for crc
  // DS18B20 & DS1822: configuration register
  scratchPad[CONFIGURATION] = _ow->read();

  // byte 5:
  // internal use & crc
  scratchPad[INTERNAL_BYTE] = _ow->read();

  // byte 6:
  // DS18S20: COUNT_REMAIN
  // DS18B20 & DS1822: store for crc
  scratchPad[COUNT_REMAIN] = _ow->read();

  // byte 7:
  // DS18S20: COUNT_PER_C
  // DS18B20 & DS1822: store for crc
  scratchPad[COUNT_PER_C] = _ow->read();

  // byte 8:
  // SCTRACHPAD_CRC
  scratchPad[SCRATCHPAD_CRC] = _ow->read();

  _ow->reset();
}
