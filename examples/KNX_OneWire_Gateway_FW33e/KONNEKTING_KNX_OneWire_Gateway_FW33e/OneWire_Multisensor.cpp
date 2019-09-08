#include <Wire.h>
#include <arduino.h>
#include <math.h>
#include <DebugUtil.h>


#include "OneWire_Multisensor.h"

//#define DebugInfo
//#define DebugInfo2
//#define DebugInfoTemp


MultiSensor::MultiSensor()
{
  // Address is determined by two pins on the DS2482 AD1/AD0
  // Pass 0b00, 0b01, 0b10 or 0b11
  //mAddress = 0x18;
  //mError = 0;
  //Wire.begin();
};

void MultiSensor::init(DS2482_OneWire *ow , uint8_t *address_DS2438, uint8_t *address_2_DS2438, uint8_t device, bool isactive_DS2438_1, bool isactive_DS2438_2,  uint8_t diff_H, uint8_t diff_L, uint16_t diff_V) {
  _ow = ow;
  _address_DS2438 = address_DS2438;
  _address_2_DS2438 = address_2_DS2438;
  _device = device;
  _isActive_DS2438_1 = isactive_DS2438_1;
  _isActive_DS2438_2 = isactive_DS2438_2;

  _dev_hum         = bitRead(_device, 0);
  _dev_voc         = bitRead(_device, 1);
  _dev_lux         = bitRead(_device, 2);
  _dev_lux2        = bitRead(_device, 3);
  _dev_ntc         = bitRead(_device, 4);
  _dev_DS2438_Temp = bitRead(_device, 5);


  _diff_H = diff_H;
  if (_diff_H != 0)
    is_diff_H_active = true;
  _diff_L = diff_L;
  if (_diff_L != 0)
    is_diff_L_active = true;
  _diff_V = diff_V;
  if (_diff_V != 0)
    is_diff_V_active = true;

  }


void MultiSensor::init(DS2482_OneWire *ow , uint8_t *address_DS2438, uint8_t *address_2_DS2438, uint8_t *address_DS18B20, uint8_t device,  bool isactive_DS18B20, bool isactive_DS2438_1, bool isactive_DS2438_2, float diff_T, uint8_t diff_H, uint8_t diff_L, uint16_t diff_V) {
  _ow = ow;
  _address_DS2438 = address_DS2438;
  _address_2_DS2438 = address_2_DS2438;
  _address_DS18B20 = address_DS18B20;
  _device = device;
  _isActive_DS18B20 = isactive_DS18B20;
  _isActive_DS2438_1 = isactive_DS2438_1;
  _isActive_DS2438_2 = isactive_DS2438_2;

  _dev_hum         = bitRead(_device, 0);
  _dev_voc         = bitRead(_device, 1);
  _dev_lux         = bitRead(_device, 2);
  _dev_lux2        = bitRead(_device, 3);
  _dev_ntc         = bitRead(_device, 4);
  _dev_DS2438_Temp = bitRead(_device, 5);
  _dev_DS18B20     = isactive_DS18B20;

  _diff_T = diff_T;
  if (_diff_T != 0)
    is_diff_T_active = true;
  _diff_H = diff_H;
  if (_diff_H != 0)
    is_diff_H_active = true;
  _diff_L = diff_L;
  if (_diff_L != 0)
    is_diff_L_active = true;
  _diff_V = diff_V;
  if (_diff_V != 0)
    is_diff_V_active = true;

  // Wenn interner Temp-Sensor aktiv -> dann DS18B20 deaktiviert
  if (_dev_DS2438_Temp) {
    _dev_DS18B20 = false;
  }

  if (!parasite && readPowerSupply(_address_DS18B20)) parasite = true;
  bitResolution = max(bitResolution, getResolution(_address_DS18B20));
}

void MultiSensor::init(DS2482_OneWire *ow , uint8_t *address_DS2438, uint8_t *address_2_DS2438, uint8_t *address_DS18B20, uint8_t device,  bool isactive_DS18B20, bool isactive_DS2438_1, bool isactive_DS2438_2, float diff_T, uint8_t diff_H, uint8_t diff_L, uint16_t diff_V, long R1, int b_Wert ) {
  _ow = ow;
  _address_DS2438 = address_DS2438;
  _address_2_DS2438 = address_2_DS2438;
  _address_DS18B20 = address_DS18B20;
  _device = device;
  _isActive_DS18B20 = isactive_DS18B20;
  _isActive_DS2438_1 = isactive_DS2438_1;
  _isActive_DS2438_2 = isactive_DS2438_2; 

  widerstand1 = R1;                 // R1 Ohm
  bWert = b_Wert;                   // B- Wert vom NTC

  _dev_hum         = bitRead(_device, 0);
  _dev_voc         = bitRead(_device, 1);
  _dev_lux         = bitRead(_device, 2);
  _dev_lux2        = bitRead(_device, 3);
  _dev_ntc         = bitRead(_device, 4);
  _dev_DS2438_Temp = bitRead(_device, 5);
  _dev_DS18B20     = isactive_DS18B20;

  _diff_T = diff_T;
  if (_diff_T != 0)
    is_diff_T_active = true;
  _diff_H = diff_H;
  if (_diff_H != 0)
    is_diff_H_active = true;
  _diff_L = diff_L;
  if (_diff_L != 0)
    is_diff_L_active = true;
  _diff_V = diff_V;
  if (_diff_V != 0)
    is_diff_V_active = true;

  // Wenn interner Temp-Sensor aktiv -> dann DS18B20 deaktiviert
  if (_dev_DS2438_Temp) {
    _dev_DS18B20 = false;
  }

  if (!parasite && readPowerSupply(_address_DS18B20)) parasite = true;
  bitResolution = max(bitResolution, getResolution(_address_DS18B20));
}

void MultiSensor::setActive_DS18B20(bool state) {
  _isActive_DS18B20 = state;
}

bool MultiSensor::getisActive_DS18B20() {
  return _isActive_DS18B20;
}

void MultiSensor::setActive_DS2438_1(bool state) {
  _isActive_DS2438_1 = state;
}

bool MultiSensor::getisActive_DS2438_1() {
  return _isActive_DS2438_1;
}


void MultiSensor::setActive_DS2438_2(bool state) {
  _isActive_DS2438_2 = state;
}

bool MultiSensor::getisActive_DS2438_2() {
  return _isActive_DS2438_2;
}




uint8_t MultiSensor::getDevice() {
  return _device;
}

float MultiSensor::getADV_mA(float R) {
  amp = raw_amp / (4096 * R);
  return amp;
}

float MultiSensor::getADV_raw_amp() {
  return raw_amp;
}

float MultiSensor::getADC_Vin() {
  return vad;
}

float MultiSensor::getADC_Vse() {
  return vse;
}

float MultiSensor::getADC_VDD() {
  return vdd;
}

float MultiSensor::getTemp() {
  return temp;
}

float MultiSensor::getHum() {
  return hum;
}

float MultiSensor::getLux() {
  return lux;
}

float MultiSensor::getLux2() {
  return lux2;
}

uint16_t MultiSensor::getVOC() {
  return voc;
}

float MultiSensor::getNTCTemp() {
  return  ntc_temp;
}

boolean MultiSensor::newValue() {
  return _newValue;
}

void MultiSensor::clearNewValue() {
  _newValue = false;
}

void MultiSensor::setCal(float cal) {
  calValueT = cal;
}


boolean MultiSensor::get_dev_hum() {
  return _dev_hum;
}

boolean MultiSensor::get_dev_voc() {
  return _dev_voc;
}

bool MultiSensor::get_dev_lux() {
  return _dev_lux;
}

bool MultiSensor::get_dev_lux2() {
  return _dev_lux2;
}

bool MultiSensor::get_dev_ntc() {
  return _dev_ntc;
}

bool MultiSensor::get_dev_DS2438_Temp() {
  return _dev_DS2438_Temp;
}

bool MultiSensor::get_dev_DS18B20() {
  return _dev_DS18B20;
}

void MultiSensor::set_dev_DS18B20(bool state) {
  if (_dev_DS2438_Temp) {
    _dev_DS18B20 = false;
  }
  else {
    _dev_DS18B20 = state;
  }
}


void  MultiSensor::setSend_Temp(bool state) {
  _send_Temp = state;
}
void  MultiSensor::setSend_Hum(bool state) {
  _send_Hum = state;
}
void  MultiSensor::setSend_Lux(bool state) {
  _send_Lux = state;
}
void  MultiSensor::setSend_VOC(bool state) {
  _send_VOC = state;
}
bool  MultiSensor::doSend_Temp() {
  return _send_Temp;
}
bool  MultiSensor::doSend_Hum() {
  return _send_Hum;
}
bool  MultiSensor::doSend_Lux() {
  return _send_Lux;
}
bool  MultiSensor::doSend_VOC() {
  return _send_VOC;
}
void   MultiSensor::clearSend_Temp() {
  _send_Temp = false;
}
void   MultiSensor::clearSend_Hum() {
  _send_Hum = false;
}
void   MultiSensor::clearSend_Lux() {
  _send_Lux = false;
}
void   MultiSensor::clearSend_VOC() {
  _send_VOC = false;
}
bool  MultiSensor::isSend_Temp() {
  return is_diff_T_active;
}
bool  MultiSensor::isSend_Hum() {
  return is_diff_H_active;
}
bool  MultiSensor::isSend_Lux() {
  return is_diff_L_active;
}
bool  MultiSensor::isSend_VOC() {
  return is_diff_V_active;
}



boolean MultiSensor::startConversion_Temp() {

  _ow->reset();
  _ow->select(_address_DS18B20);

  _ow->write(0x44, 1);        // Wandlung mit aktivierter parasitärer Versorgung starten
  return true;
}

boolean MultiSensor::update_Temp() {

  present =  _ow->reset();
  _ow->select(_address_DS18B20);

  _ow->write(0xBE);         // Scratchpad auslesen
#ifdef DebugInfoTemp
  SerialUSB.print("Data = ");
  SerialUSB.print(present, HEX);
  SerialUSB.print(" ");
#endif

  for ( i = 0; i < 9; i++) {           // Wir brauchen 9 Byte
    data[i] =  _ow->read();
#ifdef DebugInfoTemp
    SerialUSB.print(data[i], HEX);
    SerialUSB.print(" ");
#endif
  }
#ifdef DebugInfoTemp
  SerialUSB.println();
  SerialUSB.print("CRC = ");
  SerialUSB.print(DS2482_OneWire::crc8(data, 8), HEX);
  SerialUSB.println();
#endif
  byte cfg = (data[4] & 0x60);
#ifdef DebugInfoTemp
  SerialUSB.print("cfg = ");
  SerialUSB.print(cfg, HEX);
  SerialUSB.println();
#endif
  raw = (data[1] << 8) | data[0];

  if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  else if (cfg == 0x60) raw = raw;      // 12 bit res, 750 ms

  temp = (float)raw / 16.0;

#ifdef DebugInfoTemp
  SerialUSB.print("Temp = ");
  SerialUSB.print(temp);
  SerialUSB.println("°C");
#endif
}


boolean MultiSensor::startConversion_DS2438_Temp() {

  _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0x4E, 1);         // Konfiguration in Scratchpad schreiben
  _ow->write(0x00, 1);
  _ow->write(0x08, 1);

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0x44, 1);        // Temperatur Wandlung mit aktivierter parasitärer Versorgung starten

  return true;

  //delay min 10ms
}

boolean MultiSensor::startConversion_DS2438_Temp_CH2() {

  _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0x4E, 1);         // Konfiguration in Scratchpad schreiben
  _ow->write(0x00, 1);
  _ow->write(0x08, 1);

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0x44, 1);        // Temperatur Wandlung mit aktivierter parasitärer Versorgung starten

  return true;

  //delay min 10ms
}



boolean MultiSensor::re_startConversion_DS2438_ADC() {

  present = _ow->reset();
  _ow->select(_address_DS2438);
  _ow->write(0xB4, 1);        // ADC Wandlung mit aktivierter parasitärer Versorgung starte

  return true;

  //delay 5ms
}
boolean MultiSensor::re_startConversion_DS2438_ADC_CH2() {

  present = _ow->reset();
  _ow->select(_address_2_DS2438);
  _ow->write(0xB4, 1);        // ADC Wandlung mit aktivierter parasitärer Versorgung starte

  return true;

  //delay min 5ms
}

boolean MultiSensor::startConversion_DS2438_VDD() {

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0xB8, 1);         // Speicherseite 0 auswählen
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0xBE, 1);         // Scratchpad auslesen
  _ow->write(0x00, 1);
#ifdef DebugInfo
  Debug.print("Data = ");
  Serial.print(present, HEX);
  Debug.print(" ");
#endif
  for ( i = 0; i < 9; i++) {           // Wir brauchen 9 Byte
    data[i] = _ow->read();
#ifdef DebugInfo
    Serial.print(data[i], HEX);
    Debug.print(" ");
#endif
  }
#ifdef DebugInfo
  Debug.println("");
  Debug.print("CRC = ");
  Serial.print(DS2482_OneWire::crc8(data, 8), HEX);
  Debug.println("");
#endif

  //berechnet die reele VDD Spannung am DS2438
  raw = (data[4] << 8 | data[3]);
  vdd = (float)raw / 100;

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0x4E, 1);         // Konfiguration in Scratchpad schreiben
  _ow->write(0x00, 1);
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0x44, 1);        // Wandlung mit aktivierter parasitärer Versorgung starten

  return true;
}

boolean MultiSensor::startConversion_DS2438_VDD_CH2() {

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0xB8, 1);         // Speicherseite 0 auswählen
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0xBE, 1);         // Scratchpad auslesen
  _ow->write(0x00, 1);
#ifdef DebugInfo2
  Debug.print("Data = ");
  Serial.print(present, HEX);
  Debug.print(" ");
#endif
  for ( i = 0; i < 9; i++) {           // Wir brauchen 9 Byte
    data[i] = _ow->read();
#ifdef DebugInfo2
    Serial.print(data[i], HEX);
    Debug.print(" ");
#endif
  }
#ifdef DebugInfo2
  Debug.println("");
  Debug.print("CRC = ");
  Serial.print(DS2482_OneWire::crc8(data, 8), HEX);
  Debug.println("");
#endif

  //berechnet die reele VDD Spannung am DS2438
  raw = (data[4] << 8 | data[3]);
  vdd2 = (float)raw / 100;

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0x4E, 1);         // Konfiguration in Scratchpad schreiben
  _ow->write(0x00, 1);
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0x44, 1);        // Wandlung mit aktivierter parasitärer Versorgung starten

  return true;
}




boolean MultiSensor::update() {

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0xB8, 1);         // Speicherseite 0 auswählen
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0xBE, 1);         // Scratchpad auslesen
  _ow->write(0x00, 1);
#ifdef DebugInfo
  Debug.print("Data1 = ");
  Serial.print(present, HEX);
  Debug.print(" ");
#endif

  for ( i = 0; i < 9; i++) {           // Wir brauchen 9 Byte
    data[i] = _ow->read();
#ifdef DebugInfo
    Serial.print(data[i], HEX);
    Debug.print(" ");
#endif
  }
#ifdef DebugInfo
  Debug.println("");
  Debug.print("CRC1 = ");
  Serial.print(DS2482_OneWire::crc8(data, 8), HEX);
  Debug.println("");
#endif
  
  raw = ((data[2] << 5) | (data[1] >> 3));
  raw_amp = raw;

  // Berechne Internen Temp Sensor
  if (_dev_DS2438_Temp) {
    if (temp_init == false) {
      temp_old = (float)raw * 0.03125;
      temp_init = true;
    }
    else {
      temp = (float)raw * 0.03125;
      if (is_diff_T_active) {
        if (abs(temp - temp_old)  > _diff_T)
          _send_Temp = true;
        temp_old = temp;
      }
    }
  }

  //berechnet die eingelesene ADC Spannung am DS2438
  raw = (data[4] << 8 | data[3]);
  vad = (float)raw / 100;
  
  //berechnet den eingelesenen Strom am DS2438
  raw = (data[6] << 8 | data[5]);

  // calculation LUX
  if (_dev_lux) {
    //speichert ersten Wert in OLD um später damit den aktuellen Wert vergleichen zu können. 
    if (lux_init == false) {
      Vadi =  (float)(raw * 0.2441) / 47;
      lux_old = pow(10, Vadi);
      lux_init = true;
    }
    else {
      Vadi =  (float)(raw * 0.2441) / 47;
      lux = pow(10, Vadi);
      if (is_diff_L_active) {
        if (abs(lux - lux_old)  > _diff_L)
          _send_Lux = true;
        lux_old = lux;
      }
    }
  }

  // calculation Hum   hum = (161.29 * Vadc / VDD - 25.8065)/(1.0546 - 0.00216 * T)
  if (_dev_hum) {
    //speichert ersten Wert in OLD um später damit den aktuellen Wert vergleichen zu können. 
    if (hum_init == false) {
      mes = (float)161.29 * vad / vdd;
      mes_1 = (float)mes - 25.8065;
      mes_2 = (float)(1.0546 - 0.00216 * celsius);
      hum_old = mes_1 / mes_2;
      hum_init = true;
    }
    else {
      mes = (float)161.29 * vad / vdd;
      mes_1 = (float)mes - 25.8065;
      mes_2 = (float)(1.0546 - 0.00216 * celsius);
      hum = mes_1 / mes_2;
      if (is_diff_H_active) {
        if (abs(hum - hum_old)  > _diff_H)
          _send_Hum = true;
        hum_old = hum;
      }
    }
  }

  // berechung NTC Temperatur-Wert
  if (_dev_ntc) {
    widerstandNTC = widerstand1 * ((vad / vdd) / (1 - (vad / vdd)));
    TKelvin = 1 / ((1 / Tn) + ((double)1 / bWert) * log((double)widerstandNTC / widerstand1));
    ntc_temp = TKelvin - kelvintemp;
  }

  _newValue = true;

  return true;
}

boolean MultiSensor::update_CH2() {

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0xB8, 1);         // Speicherseite 0 auswählen
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_2_DS2438);

  _ow->write(0xBE, 1);         // Scratchpad auslesen
  _ow->write(0x00, 1);
#ifdef DebugInfo2
  Debug.print("Data = ");
  Serial.print(present, HEX);
  Debug.print(" ");
#endif

  for ( i = 0; i < 9; i++) {           // Wir brauchen 9 Byte
    data[i] = _ow->read();
#ifdef DebugInfo2
    Serial.print(data[i], HEX);
    Debug.print(" ");
#endif
  }
#ifdef DebugInfo2
  Debug.println("");
  Debug.print("CRC = ");
  Serial.print(DS2482_OneWire::crc8(data, 8), HEX);
  Debug.println("");
#endif
  raw = ((data[2] << 5) | (data[1] >> 3));
  celsius = (float)raw * 0.03125;
  raw = (data[4] << 8 | data[3]);
  vad2 = (float)raw / 100;
  raw2 = (data[6] << 8 | data[5]);

  raw_amp2 = raw2;

  // calculation LUX2
  if (_dev_lux2) {
    float Vadi2 =  (float)(raw2 * 0.2441) / 47;
    lux2 = pow(10, Vadi2);
  }

  // calculation  VOC
  if (_dev_voc) {
    if (voc_init = false) {
      voc_old = vad2 * 310 + 450;
      voc_init = true;
    }
    else {
      voc = vad2 * 310 + 450;
      if (is_diff_V_active) {
        if (abs(voc - voc_old)  > _diff_V)
          _send_VOC = true;
        voc_old = voc;
      }
    }
  }


  return true;
}



// reads the device's power requirements
bool MultiSensor::readPowerSupply(const uint8_t* deviceAddress)
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
bool MultiSensor::isParasitePowerMode(void)
{
  return parasite;
}


// attempt to determine if the device at the given address is connected to the bus
bool MultiSensor::isConnected(const uint8_t* deviceAddress)
{
  ScratchPad scratchPad;
  return isConnected(deviceAddress, scratchPad);
}

// attempt to determine if the device at the given address is connected to the bus
// also allows for updating the read scratchpad
bool MultiSensor::isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  readScratchPad(deviceAddress, scratchPad);
  return (_ow->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC]);
}


// attempt to determine if the device at the given address is connected to the bus
bool MultiSensor::DS18B20_isConnected()
{
  ScratchPad scratchPad;
  return DS18B20_isConnected(_address_DS18B20, scratchPad);
}


// attempt to determine if the device at the given address is connected to the bus
// also allows for updating the read scratchpad
bool MultiSensor::DS18B20_isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  readScratchPad(deviceAddress, scratchPad);
  return (_ow->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC]);
}


// returns the global resolution
uint8_t MultiSensor::getResolution()
{
  getResolution(_address_DS18B20);
}


// returns the current resolution of the device, 9-12
// returns 0 if device not found
uint8_t MultiSensor::getResolution(const uint8_t* deviceAddress)
{
  // this model has a fixed resolution of 9 bits but getTemp calculates
  // a full 12 bits resolution and we need 750ms convert time
  if (deviceAddress[0] == DS18S20MODEL) return 12;

  ScratchPad scratchPad;
  if (DS18B20_isConnected(deviceAddress, scratchPad))
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
bool MultiSensor::setResolution(uint8_t newResolution)
{
  bitResolution = constrain(newResolution, 9, 12);

  ScratchPad scratchPad;
  if (DS18B20_isConnected(_address_DS18B20, scratchPad))
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
void MultiSensor::writeScratchPad(const uint8_t* deviceAddress, const uint8_t* scratchPad)
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
void MultiSensor::readScratchPad(const uint8_t* deviceAddress, uint8_t* scratchPad)
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


// read device's scratch pad
void MultiSensor::DS2438_readScratchPad(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  // send the command
  _ow->reset();
  _ow->select(deviceAddress);

  _ow->write(0xB8, 1);         // Speicherseite 0 auswählen
  _ow->write(0x00, 1);

  present = _ow->reset();
  _ow->select(_address_DS2438);

  _ow->write(0xBE, 1);         // Scratchpad auslesen
  _ow->write(0x00, 1);

  // Speicherseite 0
  // byte 0: Status Configuiaration
  // byte 1: temperature LSB
  // byte 2: temperature MSB
  // byte 3: voltage LSB
  // byte 4: voltage MSB
  // byte 5: current LSB
  // byte 6: current MSB
  // byte 7: Threshold
  // byte 8: SCRATCHPAD_CRC

  // read the response

  // byte 0:
  scratchPad[DS2438_STATUS] = _ow->read();

  // byte 1:
  scratchPad[DS2438_TEMP_LSB] = _ow->read();

  // byte 2:
  scratchPad[DS2438_TEMP_MSB] = _ow->read();

  // byte 3:
  scratchPad[DS2438_VOLT_LSB] = _ow->read();

  // byte 4:
  scratchPad[DS2438_VOLT_MSB] = _ow->read();

  // byte 5:
  scratchPad[DS2438_CURR_LSB] = _ow->read();

  // byte 6:
  scratchPad[DS2438_CURR_MSB] = _ow->read();

  // byte 7:
  scratchPad[DS2438_THRES] = _ow->read();

  // byte 8:
  // SCTRACHPAD_CRC
  scratchPad[DS2438_SCRATCHPAD_CRC] = _ow->read();

  _ow->reset();
}

// attempt to determine if the device at the given address is connected to the bus
bool MultiSensor::DS2438_1_isConnected()
{
  ScratchPad scratchPad;
  return DS2438_1_isConnected(_address_DS2438, scratchPad);
}

// attempt to determine if the device at the given address is connected to the bus
// also allows for updating the read scratchpad
bool MultiSensor::DS2438_1_isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  DS2438_readScratchPad(deviceAddress, scratchPad);
  return (_ow->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC]);
}

// attempt to determine if the device at the given address is connected to the bus
bool MultiSensor::DS2438_2_isConnected()
{
  ScratchPad scratchPad;
  return DS2438_2_isConnected(_address_2_DS2438, scratchPad);
}

// attempt to determine if the device at the given address is connected to the bus
// also allows for updating the read scratchpad
bool MultiSensor::DS2438_2_isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad)
{
  DS2438_readScratchPad(deviceAddress, scratchPad);
  return (_ow->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC]);
}
