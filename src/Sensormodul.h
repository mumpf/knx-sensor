#pragma once
#include <knx.h>

// Parameter with single occurance
#define LOG_NumChannels                0      // uint8_t
#define LOG_StartupDelay               1      // int32_t
#define LOG_Heartbeat                  5      // int32_t
#define LOG_ReadTimeDate               9      // 1 Bit, Bit 7
#define LOG_BuzzerInstalled            9      // 1 Bit, Bit 6
#define LOG_LedInstalled               9      // 1 Bit, Bit 5
#define LOG_EepromInstalled            9      // 1 Bit, Bit 4
#define LOG_NCN5130Installed           9      // 1 Bit, Bit 3
#define LOG_Error                     12      // 1 Bit, Bit 7
#define LOG_Dewpoint                  12      // 1 Bit, Bit 6
#define LOG_Comfort                   12      // 1 Bit, Bit 5
#define LOG_Airquality                12      // 1 Bit, Bit 4
#define LOG_Accuracy                  12      // 1 Bit, Bit 3
#define LOG_DeleteData                12      // 1 Bit, Bit 2
#define LOG_TempOffset                13      // int8_t
#define LOG_TempCycle                 14      // int32_t
#define LOG_TempDeltaAbs              18      // uint16_t
#define LOG_TempDeltaPercent          20      // uint8_t
#define LOG_TempSmooth                21      // uint8_t
#define LOG_TempExtCount              22      // 2 Bits, Bit 1-0
#define LOG_TempExtRead               22      // 1 Bit, Bit 2
#define LOG_TempIntPercent            23      // uint8_t
#define LOG_TempExt1Percent           24      // uint8_t
#define LOG_TempExt2Percent           25      // uint8_t
#define LOG_HumOffset                 26      // int8_t
#define LOG_HumCycle                  27      // int32_t
#define LOG_HumDeltaAbs               31      // uint16_t
#define LOG_HumDeltaPercent           33      // uint8_t
#define LOG_HumSmooth                 34      // uint8_t
#define LOG_HumExtCount               35      // 2 Bits, Bit 1-0
#define LOG_HumExtRead                35      // 1 Bit, Bit 2
#define LOG_HumIntPercent             36      // uint8_t
#define LOG_HumExt1Percent            37      // uint8_t
#define LOG_HumExt2Percent            38      // uint8_t
#define LOG_PreOffset                 39      // int8_t
#define LOG_PreCycle                  40      // int32_t
#define LOG_PreDeltaAbs               44      // uint16_t
#define LOG_PreDeltaPercent           46      // uint8_t
#define LOG_PreSmooth                 47      // uint8_t
#define LOG_PreExtCount               48      // 2 Bits, Bit 1-0
#define LOG_PreExtRead                48      // 1 Bit, Bit 2
#define LOG_PreIntPercent             49      // uint8_t
#define LOG_PreExt1Percent            50      // uint8_t
#define LOG_PreExt2Percent            51      // uint8_t
#define LOG_VocOffset                 52      // int8_t
#define LOG_VocCycle                  53      // int32_t
#define LOG_VocDeltaAbs               57      // uint16_t
#define LOG_VocDeltPercent            59      // uint8_t
#define LOG_VocSmooth                 60      // uint8_t
#define LOG_VocExtCount               61      // 2 Bits, Bit 1-0
#define LOG_VocExtRead                61      // 1 Bit, Bit 2
#define LOG_VocIntPercent             62      // uint8_t
#define LOG_VocExt1Percent            63      // uint8_t
#define LOG_VocExt2Percent            64      // uint8_t
#define LOG_Co2Offset                 65      // int8_t
#define LOG_Co2Cycle                  66      // int32_t
#define LOG_Co2DeltaAbs               70      // uint16_t
#define LOG_Co2DeltaPercent           72      // uint8_t
#define LOG_Co2Smooth                 73      // uint8_t
#define LOG_Co2ExtCount               74      // 2 Bits, Bit 1-0
#define LOG_Co2ExtRead                74      // 1 Bit, Bit 2
#define LOG_Co2IntPercent             75      // uint8_t
#define LOG_Co2Ext1Percent            76      // uint8_t
#define LOG_Co2Ext2Percent            77      // uint8_t
#define LOG_SensorDevice              78      // 6 Bits, Bit 6-1
#define LOG_Sensor1Wire               78      // 1 Bit, Bit 0
#define LOG_DewOffset                 79      // int8_t
#define LOG_DewCycle                  80      // int32_t
#define LOG_DewDeltaAbs               84      // uint16_t
#define LOG_DewDeltaPercent           86      // uint8_t
#define LOG_DewSmooth                 87      // uint8_t

#define LOG_Channels 10

// Parameter per channel
#define LOG_ParamBlockOffset 88
#define LOG_ParamBlockSize 110
#define LOG_fChannelDelay              0      // int32_t
#define LOG_fLogic                     4      // 8 Bits, Bit 7-0
#define LOG_fCalculate                 5      // 8 Bits, Bit 7-0
#define LOG_fTrigger                   6      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                 6      // 1 Bit, Bit 0
#define LOG_fTriggerE2                 6      // 1 Bit, Bit 1
#define LOG_fTriggerI1                 6      // 1 Bit, Bit 2
#define LOG_fTriggerI2                 6      // 1 Bit, Bit 3
#define LOG_fTriggerGateClose          7      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateOpen           8      // 8 Bits, Bit 7-0
#define LOG_fE1                        9      // 4 Bits, Bit 3-0
#define LOG_fE1Convert                 9      // 4 Bits, Bit 7-4
#define LOG_fE1Dpt                    10      // 8 Bits, Bit 7-0
#define LOG_fE1Default                11      // 2 Bits, Bit 1-0
#define LOG_fE1DefaultEEPROM          11      // 1 Bit, Bit 2
#define LOG_fE1Repeat                 12      // int32_t
#define LOG_fE2                       16      // 4 Bits, Bit 3-0
#define LOG_fE2Convert                16      // 4 Bits, Bit 7-4
#define LOG_fE2Dpt                    17      // 8 Bits, Bit 7-0
#define LOG_fE2Default                18      // 2 Bits, Bit 1-0
#define LOG_fE2DefaultEEPROM          18      // 1 Bit, Bit 2
#define LOG_fE2Repeat                 19      // int32_t
#define LOG_fE1LowDelta               23      // int32_t
#define LOG_fE1HighDelta              27      // int32_t
#define LOG_fE1LowDpt2                23      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2               24      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2               25      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2               26      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                23      // uint8_t
#define LOG_fE1HighDpt5               27      // uint8_t
#define LOG_fE1LowDpt5001             23      // uint8_t
#define LOG_fE1HighDpt5001            27      // uint8_t
#define LOG_fE1LowDpt6                23      // int8_t
#define LOG_fE1HighDpt6               27      // int8_t
#define LOG_fE1LowDpt7                23      // uint16_t
#define LOG_fE1HighDpt7               27      // uint16_t
#define LOG_fE1LowDpt8                23      // int16_t
#define LOG_fE1HighDpt8               27      // int16_t
#define LOG_fE1LowDpt9                23      // float
#define LOG_fE1HighDpt9               27      // float
#define LOG_fE1Low0Dpt17              23      // uint8_t
#define LOG_fE1Low1Dpt17              24      // uint8_t
#define LOG_fE1Low2Dpt17              25      // uint8_t
#define LOG_fE1Low3Dpt17              26      // uint8_t
#define LOG_fE1Low4Dpt17              27      // uint8_t
#define LOG_fE1Low5Dpt17              28      // uint8_t
#define LOG_fE1Low6Dpt17              29      // uint8_t
#define LOG_fE1Low7Dpt17              30      // uint8_t
#define LOG_fE1LowDptRGB              23      // int32_t
#define LOG_fE1HighDptRGB             27      // int32_t
#define LOG_fE2Low0Dpt2               31      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2               32      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2               33      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2               34      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                31      // uint8_t
#define LOG_fE2HighDpt5               35      // uint8_t
#define LOG_fE2LowDpt5001             31      // uint8_t
#define LOG_fE2HighDpt5001            35      // uint8_t
#define LOG_fE2LowDpt6                31      // int8_t
#define LOG_fE2HighDpt6               35      // int8_t
#define LOG_fE2LowDpt7                31      // uint16_t
#define LOG_fE2HighDpt7               35      // uint16_t
#define LOG_fE2LowDpt8                31      // int16_t
#define LOG_fE2HighDpt8               35      // int16_t
#define LOG_fE2LowDpt9                31      // float
#define LOG_fE2HighDpt9               35      // float
#define LOG_fE2Low0Dpt17              31      // uint8_t
#define LOG_fE2Low1Dpt17              32      // uint8_t
#define LOG_fE2Low2Dpt17              33      // uint8_t
#define LOG_fE2Low3Dpt17              34      // uint8_t
#define LOG_fE2Low4Dpt17              35      // uint8_t
#define LOG_fE2Low5Dpt17              36      // uint8_t
#define LOG_fE2Low6Dpt17              37      // uint8_t
#define LOG_fE2Low7Dpt17              38      // uint8_t
#define LOG_fE2LowDptRGB              31      // int32_t
#define LOG_fE2HighDptRGB             35      // int32_t
#define LOG_fI1                       39      // 4 Bits, Bit 7-4
#define LOG_fI1Function               40      // int32_t
#define LOG_fI2                       44      // 4 Bits, Bit 7-4
#define LOG_fI2Function               45      // int32_t
#define LOG_fOStair                   49      // 8 Bits, Bit 7-0
#define LOG_fOTimeBase                50      // 8 Bits, Bit 7-0
#define LOG_fOTime                    51      // int32_t
#define LOG_fORetrigger               55      // 8 Bits, Bit 7-0
#define LOG_fOStairOff                56      // 8 Bits, Bit 7-0
#define LOG_fOBlink                   57      // int32_t
#define LOG_fODelay                   61      // 1 Bit, Bit 7
#define LOG_fODelayOnRepeat           61      // 2 Bits, Bit 6-5
#define LOG_fODelayOnReset            61      // 1 Bit, Bit 4
#define LOG_fODelayOffRepeat          61      // 2 Bits, Bit 3-2
#define LOG_fODelayOffReset           61      // 1 Bit, Bit 1
#define LOG_fODelayOn                 62      // int32_t
#define LOG_fODelayOff                66      // int32_t
#define LOG_fORepeat                  70      // 1 Bit, Bit 7
#define LOG_fOOutputFilter            70      // 2 Bits, Bit 6-5
#define LOG_fORepeatOn                71      // int32_t
#define LOG_fORepeatOff               75      // int32_t
#define LOG_fODpt                     79      // 8 Bits, Bit 7-0
#define LOG_fOOn                      80      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                80      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                   80      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                   80      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                  81      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                  81      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                  81      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                  81      // uint8_t
#define LOG_fOOnDpt5001               81      // uint8_t
#define LOG_fOOnDpt6                  81      // int8_t
#define LOG_fOOnDpt7                  81      // uint16_t
#define LOG_fOOnDpt8                  81      // int16_t
#define LOG_fOOnDpt9                  81      // float
#define LOG_fOOnDpt16                 81      // char*, 14 Byte
#define LOG_fOOnDpt17                 81      // uint8_t
#define LOG_fOOnRGB                   81      // color, uint, 3 Byte
#define LOG_fOOnPAArea                81      // 4 Bits, Bit 7-4
#define LOG_fOOnPALine                81      // 4 Bits, Bit 3-0
#define LOG_fOOnPADevice              82      // uint8_t
#define LOG_fOOff                     95      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer               95      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                  95      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                  95      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                 96      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                 96      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                 96      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                 96      // uint8_t
#define LOG_fOOffDpt5001              96      // uint8_t
#define LOG_fOOffDpt6                 96      // int8_t
#define LOG_fOOffDpt7                 96      // uint16_t
#define LOG_fOOffDpt8                 96      // int16_t
#define LOG_fOOffDpt9                 96      // float
#define LOG_fOOffDpt16                96      // char*, 14 Byte
#define LOG_fOOffDpt17                96      // uint8_t
#define LOG_fOOffRGB                  96      // color, uint, 3 Byte
#define LOG_fOOffPAArea               96      // 4 Bits, Bit 7-4
#define LOG_fOOffPALine               96      // 4 Bits, Bit 3-0
#define LOG_fOOffPADevice             97      // uint8_t

// Communication objects per channel (multiple occurance)
#define LOG_KoOffset 40
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Communication objects with single occurance
#define LOG_KoHeartbeat 1
#define LOG_KoTime 2
#define LOG_KoDate 3
#define LOG_KoRequestValues 7
#define LOG_KoError 8
#define LOG_KoDiagnose 9
#define LOG_KoTemp 10
#define LOG_KoHum 11
#define LOG_KoPre 12
#define LOG_KoVOC 13
#define LOG_KoCo2 14
#define LOG_KoCo2b 15
#define LOG_KoDewpoint 16
#define LOG_KoComfort 17
#define LOG_KoAirquality 18
#define LOG_KoSensorAccuracy 19
#define LOG_KoExt1Temp 24
#define LOG_KoExt2Temp 25
#define LOG_KoExt1Hum 26
#define LOG_KoExt2Hum 27
#define LOG_KoExt1Pre 28
#define LOG_KoExt2Pre 29
#define LOG_KoExt1VOC 30
#define LOG_KoExt2VOC 31
#define LOG_KoExt1Co2 32
#define LOG_KoExt2Co2 33

