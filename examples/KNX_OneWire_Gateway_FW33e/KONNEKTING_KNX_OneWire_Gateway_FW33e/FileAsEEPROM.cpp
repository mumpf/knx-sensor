/*
  EEPROM like API that uses a file on a fat file system
  Copyright (c)2019 com@sirsydom.de SirSydom All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/




#include "FileAsEEPROM.h"

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT);

Adafruit_W25Q16BV_FatFs fatfs(flash);

FileAsEEPROMClass::FileAsEEPROMClass(void) : _initialized(false), _dirty(false)
{
  // Empty
}

uint8_t FileAsEEPROMClass::read(int address)
{
  if(!_initialized)
    init();
  return _eeprom.data[address];
}

void FileAsEEPROMClass::update(int address, uint8_t value)
{
  if(!_initialized)
    init();
  if(_eeprom.data[address] != value)
  {
    _dirty = true;
    _eeprom.data[address] = value;
  }
}

void FileAsEEPROMClass::write(int address, uint8_t value)
{
  update(address, value);
}

void FileAsEEPROMClass::init()
{
  #ifdef FILE_AS_EEPROM_DEBUG
  Serial.println("FileAsEEPROM: init()");
  #endif
  flash.begin(FLASH_TYPE);
  fatfs.begin();

  if(fatfs.exists(EEPROM_FILENAME))
  {
    //Serial.println("FileAsEEPROM: init() file correct, read");
    writeFile = fatfs.open(EEPROM_FILENAME, FILE_READ);
    writeFile.read(_eeprom.data, EEPROM_EMULATION_SIZE);
    writeFile.close();
  }
  else
  {
    #ifdef FILE_AS_EEPROM_DEBUG
    Serial.println("FileAsEEPROM: init() file not correct");
    Serial.println(fatfs.exists(EEPROM_FILENAME));
    #endif
    memset(_eeprom.data, 0xFF, EEPROM_EMULATION_SIZE);
    _dirty = true;
  }
  _initialized = true;
}

bool FileAsEEPROMClass::isValid()
{
  if(!_initialized)
    init();
  return _eeprom.valid;
}

void FileAsEEPROMClass::commit()
{
  #ifdef FILE_AS_EEPROM_DEBUG
  Serial.println("FileAsEEPROM: commit()");
  #endif
  if(!_initialized)
    init();
  if(_dirty)
  {
    #ifdef FILE_AS_EEPROM_DEBUG
    Serial.println("FileAsEEPROM: commit() _dirty == true");
    #endif
    _eeprom.valid = true;
    writeFile = fatfs.open(EEPROM_FILENAME, FILE_WRITE);
    #ifdef FILE_AS_EEPROM_DEBUG
    if(!writeFile) Serial.println("open failed");
    #endif
    #ifdef FILE_AS_EEPROM_DEBUG
    if(!writeFile.seek(0)) Serial.println("seek failed");
    #else
    writeFile.seek(0);
    #endif
    
    #ifdef FILE_AS_EEPROM_DEBUG
    Serial.print("chars written: ");
    Serial.println(writeFile.write(_eeprom.data, EEPROM_EMULATION_SIZE));
    Serial.print("File size now: ");
    Serial.println(writeFile.size());
    #else
    writeFile.write(_eeprom.data, EEPROM_EMULATION_SIZE);
    #endif
    writeFile.close();
  }
}

FileAsEEPROMClass FileEEPROM;
