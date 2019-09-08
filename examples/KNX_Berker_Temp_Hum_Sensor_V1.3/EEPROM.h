#include <Wire.h>

int readEeprom(int index) {//Example for 24AA02E64 eeprom chip
    // when using external storage, implement READ command here
   // return EEPROM.read(index);
  byte rdata = 0xFF;
  Wire.beginTransmission(0x50);
  Wire.write((int)(index >> 8));   // MSB
  Wire.write((int)(index & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(0x50,1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

void writeEeprom(int index, int val) {//Example for 24AA02E64 eeprom chip
    // when using external storage, implement WRITE command here
   // return EEPROM.write(index, val);
  Wire.beginTransmission(0x50);
  Wire.write((int)(index >> 8));   // MSB
  Wire.write((int)(index & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
  delay(5);//is it needed?!
}

void updateEeprom(int index, int val) {
    // when using external storage, implement UPDATE command here
    //return EEPROM.update(index, val);
    if(readEeprom(index) != val){
       writeEeprom(index,val);
    }
}



