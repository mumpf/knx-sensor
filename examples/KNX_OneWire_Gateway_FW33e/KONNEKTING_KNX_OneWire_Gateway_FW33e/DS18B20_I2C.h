/*
   OneWire_Multisensor.h

    Created on: 09.03.2018
        Author: Jens
*/

#ifndef I2C_DS18B20_H_
#define I2C_DS18B20_H_

#include <inttypes.h>
#include "DS2482_OneWire.h"

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

// Model IDs
#define DS18S20MODEL 0x10
#define DS18B20MODEL 0x28
#define DS1822MODEL  0x22
#define DS1825MODEL  0x3B

// OneWire commands
#define STARTCONVO      0x44  // Tells device to take a temperature reading and put it on the scratchpad
#define COPYSCRATCH     0x48  // Copy EEPROM
#define READSCRATCH     0xBE  // Read EEPROM
#define WRITESCRATCH    0x4E  // Write to EEPROM
#define RECALLSCRATCH   0xB8  // Reload from last known
#define READPOWERSUPPLY 0xB4  // Determine if device needs parasite power
#define ALARMSEARCH     0xEC  // Query bus for devices with an alarm condition

// Scratchpad locations
#define TEMP_LSB        0
#define TEMP_MSB        1
#define HIGH_ALARM_TEMP 2
#define LOW_ALARM_TEMP  3
#define CONFIGURATION   4
#define INTERNAL_BYTE   5
#define COUNT_REMAIN    6
#define COUNT_PER_C     7
#define SCRATCHPAD_CRC  8

// Device resolution
#define TEMP_9_BIT  0x1F //  9 bit
#define TEMP_10_BIT 0x3F // 10 bit
#define TEMP_11_BIT 0x5F // 11 bit
#define TEMP_12_BIT 0x7F // 12 bit


class I2C_DS18B20
{
  public:
    I2C_DS18B20();
    void init(DS2482_OneWire *ow, uint8_t *address_DS18B20, bool isactive, float diff_T, bool Alarm1, float Alarm1_HT, float Alarm1_TT, bool Alarm2, float Alarm2_HT, float Alarm2_TT );
    //TEMP
    boolean startConversion_Temp();
    boolean update_Temp();
    float getTemp();

    void setActive(bool state);
    bool getisActive();

    // attempt to determine if the device at the given address is connected to the bus
    bool isConnected();

    // attempt to determine if the device at the given address is connected to the bus
    bool isConnected(const uint8_t*);

    // attempt to determine if the device at the given address is connected to the bus
    // also allows for updating the read scratchpad
    bool isConnected(const uint8_t*, uint8_t*);

    // get global resolution
    uint8_t getResolution();

    // returns the device resolution: 9, 10, 11, or 12 bits
    uint8_t getResolution(const uint8_t*);

    // set resolution of a device to 9, 10, 11, or 12 bits
    bool setResolution(uint8_t newResolution);

    // write device's scratchpad
    void writeScratchPad(const uint8_t*, const uint8_t*);

    // read device's scratchpad
    void readScratchPad(const uint8_t*, uint8_t*);

    // read device's power requirements
    bool readPowerSupply(const uint8_t*);

    // returns true if the bus requires parasite power
    bool isParasitePowerMode(void);

    // returns true if send-Mode = "Wertänderung" 
    bool  isSend_Temp(void);
    // returns true if "Wertänderung" detected
    bool  doSend_Temp(void); 
    void  clearSend_Temp(void); 

    // get Alram is set
    bool getAlarm1();
    bool getAlarm1_HT();
    bool getAlarm1_TT();
    bool getAlarm2();
    bool getAlarm2_HT();
    bool getAlarm2_TT();

  private:

    // initialise bus
    void begin();
    uint8_t end();


    DS2482_OneWire *_ow;
    uint8_t *_address_DS18B20;

    uint8_t bitResolution;
    typedef uint8_t ScratchPad[9];
    bool parasite;
    bool _isActive = false;
    bool is_diff_T_active = false;
    bool temp_init = false;
    bool _send_Temp = false;

    uint8_t i;
    uint8_t present = 0;
    uint8_t type_s;
    uint8_t data[12];
    uint8_t addr_DS18B20[8];
    float celsius, temp,temp_old, calValueT;
    float _diff_T;
    int16_t raw = 0;
    int16_t raw_amp = 0;

    //Alarm 1 & 2 
    bool _alarm1 = false;
    bool _isAlarm1_HT = false;
    bool _isAlarm1_TT = false;
    float _alarm1_HT;
    float _alarm1_TT;
    bool _alarm2 = false;
    bool _isAlarm2_HT = false;
    bool _isAlarm2_TT = false;
    float _alarm2_HT;
    float _alarm2_TT;

};


#endif /* I2C_DS18B20_H_ */
