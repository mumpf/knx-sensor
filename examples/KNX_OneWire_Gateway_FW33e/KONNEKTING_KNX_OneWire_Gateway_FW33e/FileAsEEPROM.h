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

//#define FILE_AS_EEPROM_DEBUG

#ifndef FILE_AS_EEPROM_h
#define FILE_AS_EEPROM_h

#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>

#ifndef EEPROM_EMULATION_SIZE
#define EEPROM_EMULATION_SIZE 4096
#endif

#define FLASH_TYPE     SPIFLASHTYPE_W25Q16BV
#define FLASH_SS SS1 // Flash chip SS pin.
#define FLASH_SPI_PORT SPI1 // What SPI port is Flash on?

#define EEPROM_FILENAME "/eeprom1.bin"

typedef struct {
  byte data[EEPROM_EMULATION_SIZE];
  boolean valid;
} EEPROM_EMULATION;


class FileAsEEPROMClass {

  public:
    FileAsEEPROMClass(void);

    /**
     * Read an eeprom cell
     * @param index
     * @return value
     */
    uint8_t read(int);

    /**
     * Write value to an eeprom cell
     * @param index
     * @param value
     */
    void write(int, uint8_t);

    /**
     * Update a eeprom cell
     * @param index
     * @param value
     */
    void update(int, uint8_t);

    /**
     * Check whether the eeprom data is valid
     * @return true, if eeprom data is valid (has been written at least once), false if not
     */
    bool isValid();

    /**
     * Write previously made eeprom changes to the underlying flash storage
     * Use this with care: Each and every commit will harm the flash and reduce it's lifetime (like with every flash memory)
     */
    void commit();

    uint16_t length() { return EEPROM_EMULATION_SIZE; }

  private:
    void init();

    bool _initialized;
    EEPROM_EMULATION _eeprom;
    bool _dirty;
    File writeFile;
};

extern FileAsEEPROMClass FileEEPROM;

#endif
