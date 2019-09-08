#include <KonnektingDevice.h>
#include <Wire.h>


#include "kdevice_KNX_1-Wire_Gateway_firmware_33.h"
#include "DS18B20_I2C.h"
#include "DS2482_OneWire.h"
#include "OneWire_Multisensor.h"
#include "DS2408.h"




// ################################################
// ### Board
// ################################################
//#define ArduinoZero
//#define SAMDminí
#define ItsyBitsyM0
//#define TrinketM0




// ################################################
// ### Bebug Output Configuration
// ################################################

/* DEBUG-MODE  */
#define KDEBUG                  // comment this line to disable DEBUG mode

#ifdef KDEBUG
#define KDEBUG_SensorValues     // comment this line to disable DEBUG mode for Temp Sensors
#define KDEBUG_MultiSensoren    // comment this line to disable DEBUG mode for Multisensors
//#define KDEBUG_iButton_search   // comment this line to disable DEBUG mode for iButton
#define KDEBUG_KNX              // comment this line to disable DEBUG mode for KNX messages
#endif


// ################################################
// ### IO Configuration
// ################################################
#ifdef ArduinoZero
#define PROG_LED_PIN      26
#define PROG_BUTTON_PIN   A1
#define LED_YELLOW        25
#define I2CEEPROM                 //-> save the GA / Paramters in a I2C EEPROM
#endif

#ifdef ItsyBitsyM0
#define PROG_LED_PIN      9
#define PROG_BUTTON_PIN   A1
#define LED_YELLOW        13
//#define I2CEEPROM                //-> save the GA / Paramters in the external EEPROM
//#define FLASH                    //-> save the GA / Paramters in the internal Flash
#define SPIFLASH                   //-> save the GA / Paramters in the internal SPI-Flash
#endif

#ifdef SPIFLASH
#include "FileAsEEPROM.h"
#endif


// ################################################
// ### KONNEKTING Debug
// ################################################
#ifdef KDEBUG
#include <DebugUtil.h>
#ifdef ArduinoZero
#define DEBUGSERIAL SerialUSB
#endif
#ifdef ItsyBitsyM0
#include "FileAsEEPROM.h"
#define DEBUGSERIAL Serial
#endif
#endif




// ################################################
// ### KONNEKTING Configuration
// ################################################
#define KNX_SERIAL Serial1  // Leonardo/Micro/ZERO etc. use Serial1


// ################################################
// ### oneWire  DS2482-100
// ################################################
DS2482_OneWire oneWire_CH1(1);      //I2C Adresse = 0x19      links
DS2482_OneWire oneWire_CH2(3);      //I2C Adresse = 0x1B      rechts
DS2482_OneWire oneWire_CH3(2);      //I2C Adresse = 0x1A      unten

// ################################################
// ### define OneWire DS2408 Switch
// ################################################
DS2408 DS2408_SW;
DS2408 DS2408_SW_2;
uint8_t DS2408_address[] = { 0x25, 0x22, 0x66, 0x2F, 0x00, 0x00, 0x00, 0x9C };
uint8_t DS2408_address_2[] = { 0x25, 0x21, 0x66, 0x2F, 0x00, 0x00, 0x00, 0xC5 };
uint8_t DS2408_found = 0;
uint8_t DS2408_found_2 = 0;

// ################################################
// ### define OneWire Power mode DS18B20
// ### aktivate only one of this postions
// ################################################
//#define paratiticMODE
#define NONparatiticMODE

// ################################################
// ### define OneWire Temp Sensor DS18B20
// ################################################
#define COUNT_DS18B20      42
#define COUNT_DS18B20_S1   14
#define COUNT_DS18B20_S2   14
#define COUNT_DS18B20_S3   14
I2C_DS18B20 DS18B20[COUNT_DS18B20];
I2C_DS18B20 DS18B20_S1[COUNT_DS18B20_S1];
I2C_DS18B20 DS18B20_S2[COUNT_DS18B20_S2];
I2C_DS18B20 DS18B20_S3[COUNT_DS18B20_S3];


// ################################################
// ### define ibutton
// ################################################
#define MAX_iButton 10
#define MAX_loop_Count 5



// ################################################
// ### define OneWire Multisensor
// ################################################
#define MAX_multisenor 10
#define MAX_multisenor_o_NTC 5
#define MAX_multisenor_m_NTC 5
MultiSensor multiSensor[MAX_multisenor];


// ################################################
// ### define KNX MSG
// ################################################
#define CountMSGtemp 2   //Damit erst Werte eingelesen werden bevor eine KNX MSG verschickt wird
#define CountMSGms 2

FILE test;

// ################################################
// ### KONNEKTING Parameter
// ################################################
//1-Wire CH
boolean oneW_CH1_ON = false;
boolean oneW_CH2_ON = false;
boolean oneW_CH3_ON = false;
boolean oneW_CH1_StrongPU_ON = false;
boolean oneW_CH2_StrongPU_ON = false;
boolean oneW_CH3_StrongPU_ON = false;

// Alive MSG
bool alive_msg_ON = true;
uint8_t alive_msg_time;

//New ID
boolean sendNewID = false;
boolean readNewID = false;
uint8_t readNewID_bus = 1;

//DS18B20
boolean sendKNXtempCH1 = true;
boolean sendKNXtempCH2 = true;
boolean sendKNXtempCH3 = true;
boolean sendKNXtemp_aenderung_CH1 = true;
boolean sendKNXtemp_aenderung_CH2 = true;
boolean sendKNXtemp_aenderung_CH3 = true;
float diff_T_S1[COUNT_DS18B20] = {0};
float diff_T_S2[COUNT_DS18B20] = {0};
float diff_T_S3[COUNT_DS18B20] = {0};
float Alarm_1_HT[3] = {0};
float Alarm_1_TT[3] = {0};
float Alarm_2_HT[3] = {0};
float Alarm_2_TT[3] = {0};
uint16_t Sensor_Alarm1[3] = {0};
uint16_t Sensor_Alarm2[3] = {0};
uint8_t TempResolution_CH1 = 2;
uint8_t TempResolution_CH2 = 2;
uint8_t TempResolution_CH3 = 2;
uint8_t resolution[4] = {9, 10, 11, 12};
uint8_t DS18B20_address[COUNT_DS18B20][8] = { 0 };
uint8_t DS18B20_address_S1[COUNT_DS18B20][8] = { 0 };
uint8_t DS18B20_address_S2[COUNT_DS18B20][8] = { 0 };
uint8_t DS18B20_address_S3[COUNT_DS18B20][8] = { 0 };

//iButton
uint8_t readiButton_bus = 2;
bool sendKNXiButtons = true;
uint8_t checkSteps = 5;   // maximal wie MAX_loop_Count
boolean infoWrongID = 0;
uint8_t alive_Interval = 0;
uint8_t polliButton = 0;
boolean sendZyklStatus = 0;
boolean allAbwSend = 0;
boolean allAnwSend = 0;
uint8_t delayALLAbw = 0;
uint8_t blockiButtons = 0;
boolean sendinfoWrongID = 0;
boolean allAbw_B_S = 0;
uint8_t szenenWahl = 0;
uint16_t AbwGruppe1 = 0;
uint16_t AbwGruppe2 = 0;
uint16_t AbwGruppe3 = 0;
bool iButtonDoorReq[]    = {false, false, false, false, false, false, false, false, false, false};
byte iButtonInvOutput[]  = {false, false, false, false, false, false, false, false, false, false};
bool iButtonActive[]     = {false, false, false, false, false, false, false, false, false, false};
byte iButtonComObj[] = {COMOBJ_iButtonID1,
                        COMOBJ_iButtonID2,
                        COMOBJ_iButtonID3,
                        COMOBJ_iButtonID4,
                        COMOBJ_iButtonID5,
                        COMOBJ_iButtonID6,
                        COMOBJ_iButtonID7,
                        COMOBJ_iButtonID8,
                        COMOBJ_iButtonID8,
                        COMOBJ_iButtonID10
                       };
byte iButton0[8];
byte iButton1[8];
byte iButton2[8];
byte iButton3[8];
byte iButton4[8];
byte iButton5[8];
byte iButton6[8];
byte iButton7[8];
byte iButton8[8];
byte iButton9[8];



//Multisensor
bool sendKNXmultisensor = true;
bool sendKNXMS_aenderung = true;
float ms_diff_T[MAX_multisenor] = {0};
uint8_t ms_diff_H[MAX_multisenor] = {0};
uint8_t ms_diff_L[MAX_multisenor] = {0};
uint16_t ms_diff_V[MAX_multisenor] = {0};
//float ms_temp_cal_wert[MAX_multisenor] = {0};
long NTC_R1[MAX_multisenor] = {0};               
int  NTC_bWert[MAX_multisenor] = {0};                          

uint8_t oneWire_MS_CH[MAX_multisenor] = {3};
uint8_t ms_Resolution[MAX_multisenor] = {2};
uint8_t ms_Device[MAX_multisenor] = {0};
uint8_t ms_DS2438_address[MAX_multisenor][8];
uint8_t ms_DS2438_2_address[MAX_multisenor][8];
uint8_t ms_DS18B20_address[MAX_multisenor][8];





// ################################################
// ### define Timer Counter
// ################################################

// Timer sent new ID
unsigned start_search_ID = 0;
uint32_t sent_ID_counter = 0;
uint32_t read_ID_counter = 0;
unsigned long start_sent_ID_Millis;
unsigned long current_sent_ID_Millis;

// Alive MSG 
uint32_t sent_alive_counter = 0;
unsigned long start_alive_msg_Millis = 0;
unsigned long current_alive_msg_Millis;

//DS18B20
uint32_t sent_temp_counterCH1 = 0;
uint32_t sent_temp_counterCH2 = 0;
uint32_t sent_temp_counterCH3 = 0;
uint32_t sent_temp_aenderung_counterCH1 = 0;
uint32_t sent_temp_aenderung_counterCH2 = 0;
uint32_t sent_temp_aenderung_counterCH3 = 0;
uint32_t read_temp_counter = 10000;
unsigned long start_read_Temp_Millis = 0;
unsigned long current_read_Temp_Millis;
unsigned long start_conversation = 0;
unsigned long start_sent_Tvalue_Millis_CH1 = 0;
unsigned long current_sent_Tvalue_Millis_CH1;
unsigned long start_sent_Tvalue_Millis_CH2 = 0;
unsigned long current_sent_Tvalue_Millis_CH2;
unsigned long start_sent_Tvalue_Millis_CH3 = 0;
unsigned long current_sent_Tvalue_Millis_CH3;
unsigned long start_sent_aenderung_Tvalue_Millis_CH1[COUNT_DS18B20_S1] = {0};
unsigned long start_sent_aenderung_Tvalue_Millis_CH2[COUNT_DS18B20_S2] = {0};
unsigned long start_sent_aenderung_Tvalue_Millis_CH3[COUNT_DS18B20_S3] = {0};

//iButton
uint32_t poll_counter = 0;
uint32_t delay_counter = 0;
uint32_t freq_sent_counter = 0;
unsigned long start_poll_Millis;
unsigned long current_poll_Millis;
unsigned long start_delay_Abw_Millis;
unsigned long current_delay_Abw_Millis;

// Multisensor
uint32_t sent_multi_counter = 0;
uint32_t read_multi_counter = 0;
unsigned long start_sent_Multi_Millis = 0;
unsigned long current_sent_Multi_Millis;
unsigned long start_conversationM[4];
unsigned long ms_start_conversation = 0;
unsigned long sent_MS_aenderung_counter = 0;
unsigned long start_sent_aenderung_HUM_MS_Millis[MAX_iButton] = {0};
unsigned long start_sent_aenderung_LUX_MS_Millis[MAX_iButton] = {0};
unsigned long start_sent_aenderung_VOC_MS_Millis[MAX_iButton] = {0};
unsigned long wait_1 = 750;
unsigned long wait_2 = 20;
unsigned long wait_3 = 20;
unsigned long wait_4 = 20;
unsigned long wait_5 = 20;
unsigned long wait_6 = 20;

// LUX-Sensor
unsigned long start_conversation_Lux = 0;




// ################################################
// ### define state machine
// ################################################
typedef enum  {
  initState,
  iButtonRead,
  read_NewID,
  KNXmsg,
  Group1
} StateMaschineMain;
StateMaschineMain state_1 = initState;

typedef enum  {
  requestTemp,
  readMultisensor_DS18b20,
  readMultisensor_DS2438
} StateMaschine2nd;
StateMaschine2nd state_2 = requestTemp;


//typedef enum  {
//  requestTemp,
//  readiButton,
//  readMultisensor,
//  KNXmsg,
//  readnewID
//} deviceStates;
//deviceStates stateloop = requestTemp;

typedef enum  {
  ID_search,
  ID_check,
  Sent_ID,
} OneWireSearchID;
OneWireSearchID searchIDOneWire = ID_search;

typedef enum  {
  startConTemp,
  update_Temp,
  wait
} TempSensor;
TempSensor TempSensorState = startConTemp;

typedef enum  {
  ms_startConTemp,
  ms_update_Temp,
  ms_wait
} MS_TempSensor;
MS_TempSensor MS_TempSensorState = ms_startConTemp;

typedef enum  {
  iButton_search,
  iButton_check,
  iButton_status
} IButtonSearchState;
IButtonSearchState iButtonStateOneWire = iButton_search;

typedef enum  {
  wait_allAbw,
  wait_delay,
  sendAllAbw,
  stopAbw
} iButtonAbw_State;
iButtonAbw_State state_iButtonAbw = stopAbw;

typedef enum  {
  CH1_Temp1_5,
  CH1_Temp6_10,
  CH1_Temp11_14,
} KNXMSG_CH1;
KNXMSG_CH1 stateKNXsend_CH1 = CH1_Temp1_5;

typedef enum  {
  CH2_Temp15_19,
  CH2_Temp20_24,
  CH2_Temp25_28,
} KNXMSG_CH2;
KNXMSG_CH2 stateKNXsend_CH2 = CH2_Temp15_19;

typedef enum  {
  CH3_Temp29_33,
  CH3_Temp34_38,
  CH3_Temp39_42,
} KNXMSG_CH3;
KNXMSG_CH3 stateKNXsend_CH3 = CH3_Temp29_33;

typedef enum  {
  Temp1_5,
  Temp6_10,
  Temp11_14,
  Temp15_19,
  Temp20_24,
  Temp25_28,
  Temp29_33,
  Temp34_38,
  Temp39_42,
} KNXMSG;
KNXMSG stateKNXsend = Temp1_5;

typedef enum  {
  MultiS_1,
  MultiS_2,
  MultiS_3,
  MultiS_4,
  MultiS_5,
  MultiS_6,
  MultiS_7,
  MultiS_8,
  MultiS_9,
  MultiS_10
} MS_KNXMSG;
MS_KNXMSG ms_stateKNXsend = MultiS_1;

typedef enum  {
  startConTemp_DS18B20,
  update_Temp_DS18B20,
  startCon_DS2438_Temp,
  startCon_DS2438_ADC,
  update_DS2438_VDD,
  re_startCon_DS2438_ADC,
  update_DS2438_VAD
} MultiSensorStates;
MultiSensorStates ReadSensor[4] = {startConTemp_DS18B20, startConTemp_DS18B20, startConTemp_DS18B20, startConTemp_DS18B20};
MultiSensorStates Read_DS2438_Sensor = startCon_DS2438_Temp ;

// ################################################
// ### gobal variables 1-Wire CH
// ################################################
boolean CH1_active = false;
boolean CH2_active = false;
boolean CH3_active = false;
boolean CH1_short = false;
boolean CH1_short_old = false;
boolean CH2_short = false;
boolean CH2_short_old = false;
boolean CH3_short = false;
boolean CH3_short_old = false;
boolean CH1_I2C_Master_Error = false;
boolean CH2_I2C_Master_Error = false;
boolean CH3_I2C_Master_Error = false;

// ################################################
// ### gobal variables read new Sensor ID
// ################################################
byte new_ID_addrArray[COUNT_DS18B20_S1 + (2 * MAX_multisenor)][8];
byte newIdAddr[8];
boolean readytoRead = false;
boolean newID = false;
boolean firstsend = false;
boolean newIDpos[COUNT_DS18B20] = {0};
byte validID = 0;
byte countID = 0;
byte counter = 0;
byte readCout = 0;

// ################################################
// ### gobal variables read DS18B20
// ################################################
boolean initalSend = true;
boolean finishRead = false;
byte step_count = 0;
byte step_count_aenderung = 0;
boolean tempSensorActive[COUNT_DS18B20_S1 + COUNT_DS18B20_S2  + COUNT_DS18B20_S3] = {0};
boolean tempSensorActive_S1[COUNT_DS18B20_S1] = {0};
boolean tempSensorActive_S2[COUNT_DS18B20_S2] = {0};
boolean tempSensorActive_S3[COUNT_DS18B20_S3] = {0};
boolean tempSensorError[COUNT_DS18B20_S1  + COUNT_DS18B20_S2  + COUNT_DS18B20_S3] = {0};
boolean tempSensorError_S1[COUNT_DS18B20_S1] = {0};
boolean tempSensorError_S2[COUNT_DS18B20_S2] = {0};
boolean tempSensorError_S3[COUNT_DS18B20_S3] = {0};
uint16_t SensorError_temp_S1 = 0;
uint16_t SensorError_temp_S2 = 0;
uint16_t SensorError_temp_S3 = 0;
uint16_t SensorError_temp_old_S1 = 0;
uint16_t SensorError_temp_old_S2 = 0;
uint16_t SensorError_temp_old_S3 = 0;
boolean tempSensorConnect[COUNT_DS18B20_S1  + COUNT_DS18B20_S2  + COUNT_DS18B20_S3] = {0};
boolean tempSensorConnect_S1[COUNT_DS18B20_S1] = {0};
boolean tempSensorConnect_S2[COUNT_DS18B20_S2] = {0};
boolean tempSensorConnect_S3[COUNT_DS18B20_S3] = {0};
boolean isAlarm1_HT_aktiv[3] = {false, false, false};
boolean isAlarm1_TT_aktiv[3] = {false, false, false};
boolean isAlarm2_HT_aktiv[3] = {false, false, false};
boolean isAlarm2_TT_aktiv[3] = {false, false, false};
uint16_t isAlarm1_HT_sensors[3] = {0};
uint16_t isAlarm1_TT_sensors[3] = {0};
uint16_t isAlarm2_HT_sensors[3] = {0};
uint16_t isAlarm2_TT_sensors[3] = {0};

// ################################################
// ### gobal variables iButton
// ################################################
boolean iButton_search_error = false;
boolean iButton_unreg_det = false;
boolean iButtonGroup1_det = false;
boolean iButtonGroup2_det = false;
boolean iButtonGroup3_det = false;
boolean firstAbsentSet = false;
boolean delayAbgelaufen = false;
boolean iButton_State_send = true;
boolean iButton_allAbw_delay = true;
boolean lastState_present = false;
boolean lastState_one_absent = true;
boolean lastState_absent = true;
boolean lastState_unreg = true;
boolean iButtonRequest = false;

byte iButton_count_old = 10;
byte iButton_unreg_count = 0;
byte iButton_unreg_count_old = 0;

byte iButton_addrArray[MAX_iButton][8];
byte iButton_unreg_addr_Array[MAX_iButton][8];

bool iButtonListArray[MAX_loop_Count][MAX_iButton]  = {0};
bool iButtonState[]      = {true, true, true, true, true, true, true, true, true, true};
bool iButtonLastState[]  = {false, false, false, false, false, false, false, false, false, false};
bool iButtonUnregistered = false;

bool setLEDiButton[8] = {false};
bool stateLEDiButton[8] = {false};


// ################################################
// ### gobal variables iButton
// ################################################
byte ms_DS18B20_step_count = 0;
byte ms_DS2438_step_count = 0;
byte ms_step_count_aenderung = 0;
boolean ms_DS18B20_tempSensorError[MAX_multisenor] = {0};
boolean ms_DS2438_1_tempSensorError[MAX_multisenor] = {0};
boolean ms_DS2438_2_tempSensorError[MAX_multisenor] = {0};
boolean ms_DS18B20_Active[MAX_multisenor] = {0};
boolean ms_DS2438_1_Active[MAX_multisenor] = {0};
boolean ms_DS2438_2_Active[MAX_multisenor] = {0};


// ################################################
// ### gobal variables KNX MSG
// ################################################
uint8_t knx_msg_count_temp = 0;
uint8_t knx_msg_count_ms = 0;
bool knx_send = false;

#include "EEPROM.h"
#include "3_readSensorID.h"
#include "4_readSensor.h"
#include "5_iButton.h"
#include "6_Multisensor.h"
#include "2_KNX_Message.h"
#include "0_setup.h"
