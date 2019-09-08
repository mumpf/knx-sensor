/*
   OneWire_Multisensor.h

    Created on: 09.03.2018
        Author: Jens
*/

#ifndef OneWire_Multisensor_H_
#define OneWire_Multisensor_H_

#include <inttypes.h>
#include "DS2482_OneWire.h"

// Device
/*
   VOC             = 1
   HUM             = 2
   VOC + HUM       = 3
   HUM + LUX       = 5
   VOC + LUX       = 6
   VOC + HUM + LUX = 7
   LUX + NTC       = 20
   VOC + LUX + NTC = 22
   LUX + LUX + NTC = 28
   HUM + interner Temp  = 32
*/

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

// Scratchpad locations DS18B20
#define TEMP_LSB        0
#define TEMP_MSB        1
#define HIGH_ALARM_TEMP 2
#define LOW_ALARM_TEMP  3
#define CONFIGURATION   4
#define INTERNAL_BYTE   5
#define COUNT_REMAIN    6
#define COUNT_PER_C     7
#define SCRATCHPAD_CRC  8

// Scratchpad locations DS2438
#define DS2438_STATUS          0
#define DS2438_TEMP_LSB        1
#define DS2438_TEMP_MSB        2
#define DS2438_VOLT_LSB        3
#define DS2438_VOLT_MSB        4
#define DS2438_CURR_LSB        5
#define DS2438_CURR_MSB        6
#define DS2438_THRES           7
#define DS2438_SCRATCHPAD_CRC  8

// Device resolution
#define TEMP_9_BIT  0x1F //  9 bit
#define TEMP_10_BIT 0x3F // 10 bit
#define TEMP_11_BIT 0x5F // 11 bit
#define TEMP_12_BIT 0x7F // 12 bit
 

class MultiSensor
{
  public:

    MultiSensor();
    void init(DS2482_OneWire *ow , uint8_t *address_DS2438, uint8_t *address_2_DS2438, uint8_t device, bool isactive_DS2438_1, bool isactive_DS2438_2,  uint8_t diff_H, uint8_t diff_L, uint16_t diff_V);
    void init(DS2482_OneWire *ow , uint8_t *address_DS2438, uint8_t *address_2_DS2438, uint8_t *address_DS18B20, uint8_t device,  bool isactive_DS18B20, bool isactive_DS2438_1, bool isactive_DS2438_2, float diff_T, uint8_t diff_H, uint8_t diff_L, uint16_t diff_V);
    void init(DS2482_OneWire *ow , uint8_t *address_DS2438, uint8_t *address_2_DS2438, uint8_t *address_DS18B20, uint8_t device,  bool isactive_DS18B20, bool isactive_DS2438_1, bool isactive_DS2438_2, float diff_T, uint8_t diff_H, uint8_t diff_L, uint16_t diff_V, long R1, int b_Wert );
    //TEMP
    boolean startConversion_Temp();
    boolean update_Temp();
    bool setResolution(uint8_t newResolution);


    //HUM + LUX + VOC
    boolean startConversion_DS2438_Temp();
    boolean startConversion_DS2438_Temp_CH2();
    boolean re_startConversion_DS2438_ADC();
    boolean re_startConversion_DS2438_ADC_CH2();
    boolean startConversion_DS2438_VDD();
    boolean startConversion_DS2438_VDD_CH2();
    boolean update();
    boolean update_CH2();
    uint8_t bitResolution;
    typedef uint8_t ScratchPad[9];

    bool isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad);
    bool isConnected(const uint8_t* deviceAddress);

    // attempt to determine if the device at the given address is connected to the bus
    bool DS18B20_isConnected();
    bool DS2438_1_isConnected();
    bool DS2438_2_isConnected();

    // attempt to determine if the device at the given address is connected to the bus
    // also allows for updating the read scratchpad
    bool DS18B20_isConnected(const uint8_t*, uint8_t*);
    bool DS2438_1_isConnected(const uint8_t*, uint8_t*);
    bool DS2438_2_isConnected(const uint8_t*, uint8_t*);

    // get global resolution
    uint8_t getResolution();

    // returns the device resolution: 9, 10, 11, or 12 bits
    uint8_t getResolution(const uint8_t*);

    // write device's scratchpad
    void writeScratchPad(const uint8_t*, const uint8_t*);

    // read device's scratchpad
    void readScratchPad(const uint8_t*, uint8_t*);
    void DS2438_readScratchPad(const uint8_t*, uint8_t*);


    // read device's power requirements
    bool readPowerSupply(const uint8_t*);

    // returns true if the bus requires parasite power
    bool isParasitePowerMode(void);

    void setActive_DS18B20(bool state);
    bool getisActive_DS18B20();

    void setActive_DS2438_1(bool state);
    bool getisActive_DS2438_1();

    void setActive_DS2438_2(bool state);
    bool getisActive_DS2438_2();

    // sende Routinen
    void setSend_Temp(bool state);
    void setSend_Hum(bool state);
    void setSend_Lux(bool state);
    void setSend_VOC(bool state);
    bool doSend_Temp();
    bool doSend_Hum();
    bool doSend_Lux();
    bool doSend_VOC();
    bool isSend_Temp();
    bool isSend_Hum();
    bool isSend_Lux();
    bool isSend_VOC();
    void  clearSend_Temp(void); 
    void  clearSend_Hum(void); 
    void  clearSend_Lux(void); 
    void  clearSend_VOC(void); 


    // return Devices
    bool get_dev_hum(void);
    bool get_dev_voc(void);
    bool get_dev_lux(void);
    bool get_dev_lux2(void);
    bool get_dev_ntc(void);
    bool get_dev_DS2438_Temp(void);
    bool get_dev_DS18B20(void);
    void set_dev_DS18B20(bool state);


    float getTemp();
    float getHum();
    float getLux();
    float getLux2();
    uint16_t getVOC();
    float getNTCTemp();

    uint8_t getDevice();
    float getADC_Vin();
    float getADC_Vse();
    float getADV_mA(float R);
    float getADV_raw_amp();
    float getADC_VDD();
    boolean newValue();
    void clearNewValue();
    void setCal(float cal);
    bool parasite;







  private:
    void begin();
    uint8_t end();


    DS2482_OneWire *_ow;
    uint8_t *_address_DS2438;
    uint8_t *_address_2_DS2438;
    uint8_t *_address_DS18B20;
    boolean _newValue = false;
    uint8_t _device;
    bool _isActive_DS18B20 = false;
    bool _isActive_DS2438_1 = false;
    bool _isActive_DS2438_2 = false;


    boolean _dev_hum = false;
    boolean _dev_voc = false;
    boolean _dev_lux = false;
    boolean _dev_lux2 = false;
    boolean _dev_ntc = false;
    boolean _dev_DS2438_Temp = false;
    boolean _dev_DS18B20 = true;

    boolean _send_Temp = false;
    boolean _send_Hum = false;
    boolean _send_Lux = false;
    boolean _send_VOC = false;

    uint8_t i;
    uint8_t present = 0;
    uint8_t type_s;
    uint8_t data[12];
    uint8_t addr_DS2438[8];
    uint8_t addr_DS18B20[8];
    float celsius, vdd, vad, vse, amp;
    float celsius2, vdd2, vad2, vse2, amp2;

    //Sprung values senden
    float _diff_T;
    uint8_t _diff_H;
    uint8_t _diff_L;
    uint16_t _diff_V;
    //aktiv
    bool is_diff_T_active = false;
    bool is_diff_H_active = false;
    bool is_diff_L_active = false;
    bool is_diff_V_active = false;



    char add;
    int16_t raw_amp = 0;
    int16_t raw = 0;
    int16_t raw2 = 0;
    int16_t raw_amp2 = 0;

    //Temp
    float temp, temp_old, calValueT;
    bool temp_init = false;

    //LUX
    float Vadi;
    int lux, lux_old;
    int lux2;
    bool lux_init = false;

    //HUM
    float  hum, hum_old;
    float  mes ;
    float  mes_1;
    float  mes_2;
    bool hum_init = false;

    //VOC
    uint16_t voc, voc_old;
    bool voc_init = false;

    //NTC
    int bitwertNTC = 0;
    long widerstand1 = 100000;                 //Ohm
    int bWert = 3950;                          // B- Wert vom NTC
    double widerstandNTC = 0;
    double kelvintemp = 273.15;                // 0°Celsius in Kelvin
    double Tn = kelvintemp + 25;               //Nenntemperatur in Kelvin
    double TKelvin = 0;                        //Die errechnete Isttemperatur
    double T = 0;                              //Die errechnete Isttemperatur
    float ntc_temp;




};


#endif /* OneWire_MultisensorY_H_ */
