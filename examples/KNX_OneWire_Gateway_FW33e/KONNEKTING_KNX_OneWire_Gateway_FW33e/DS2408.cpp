#include "DS2408.h"
#include <arduino.h>
#include <stdio.h>
#include <Wire.h>



DS2408::DS2408() {

};


void DS2408::init(DS2482_OneWire *onew , uint8_t *address_DS2408) {

  _ow = onew;
  _address_DS2408 = address_DS2408;

}


bool DS2408::set_LED_DS2408(uint8_t led, bool state) {

  byte temp = get_state();

  if (state)
    bitClear(temp, led);
  else
    bitSet(temp, led);

   return set_state(temp);
}


uint8_t DS2408::get_register(Register reg) {
  select_device(_address_DS2408);
  _ow->write(DS2408_PIO_READ_CMD, 1);
  _ow->write(REG_LO(reg), 1);
  _ow->write(REG_HI(reg), 1);
  return _ow->read();
}




void DS2408::set_register(Register reg, uint8_t value) {
  select_device(_address_DS2408);
  _ow->write(DS2408_SEARCH_CMD, 1);
  _ow->write(REG_LO(reg), 1);
  _ow->write(REG_HI(reg), 1);
  _ow->write(value, 1);
}




uint8_t DS2408::get_state() {
  select_device(_address_DS2408);
  _ow->write(DS2408_CHANNEL_READ_CMD, 1);
  return  _ow->read();
}

bool DS2408::set_state( uint8_t state) {
  select_device(_address_DS2408);
  _ow->write(DS2408_CHANNEL_WRITE_CMD, 1);
  _ow->write(state, 1);
  _ow->write(~state, 1);
  if (_ow->read() == 0xAA && _ow->read() == state)
    return true;
  return false;
}



void DS2408::set_search_mask(uint8_t mask) {
  select_device(_address_DS2408);
  set_register(DS2408_SEARCH_MASK_REG, mask);
}



void DS2408::set_search_polarity(uint8_t polarity) {
  select_device(_address_DS2408);
  set_register(DS2408_SEARCH_SELECT_REG, polarity);
}



void    DS2408::set_mode(uint8_t mode) {
  select_device(_address_DS2408);
  set_register(DS2408_CONTROL_STATUS_REG, mode);
}


uint8_t DS2408::get_mode() {
  select_device(_address_DS2408);
  return get_register(DS2408_CONTROL_STATUS_REG);
}


uint8_t DS2408::get_current_state() {
  select_device(_address_DS2408);
  return get_register(DS2408_PIO_LOGIC_REG);
}




uint8_t DS2408::get_last_state() {
  select_device(_address_DS2408);
  return get_register(DS2408_PIO_OUTPUT_REG);
}




uint8_t DS2408::get_activity() {
  select_device(_address_DS2408);
  return get_register(DS2408_PIO_ACTIVITY_REG);
}



bool DS2408::reset_activity() {
  select_device(_address_DS2408);
  _ow->write(DS2408_RESET_CMD, 1);
  if (_ow->read() == 0xAA)
    return true;
  return false;
}




void DS2408::select_device(Device device) {
  _ow->reset();
  _ow->select(_address_DS2408);
}




uint8_t  DS2408::find() {
  uint8_t count = 0;
  while (_ow->search(_address_DS2408)) {
    if (_address_DS2408[0] == DS2408_FAMILY) {
      count++;
    }
  }
  _ow->reset_search();
  delay(250);
  //
  //  *_address_DS2408 = (_address_DS2408) malloc(count * sizeof(_address_DS2408));
  //  for (int index = 0; index < count; index++)
  //    _ow->search((*_address_DS2408)[index]);
  return count;
}
