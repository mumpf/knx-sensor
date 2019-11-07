#pragma once
#include <knx.h>

// Parameter with single occurance
#define LOG_NumChannels                0      // int32_t
#define LOG_StartupDelay               4      // int32_t
#define LOG_Heartbeat                  8      // int32_t
#define LOG_Error                     12      // 1 Bit, Bit 7
#define LOG_TempOffset                13      // int8_t
#define LOG_TempCycle                 14      // int32_t
#define LOG_TempDeltaAbs              18      // uint16_t
#define LOG_TempDeltaPercent          20      // uint8_t
#define LOG_TempSmooth                21      // uint8_t
#define LOG_HumOffset                 22      // int8_t
#define LOG_HumCycle                  23      // int32_t
#define LOG_HumDeltaAbs               27      // uint16_t
#define LOG_HumDeltaPercent           29      // uint8_t
#define LOG_HumSmooth                 30      // uint8_t
#define LOG_PreOffset                 31      // int8_t
#define LOG_PreCycle                  32      // int32_t
#define LOG_PreDeltaAbs               36      // uint16_t
#define LOG_PreDeltaPercent           38      // uint8_t
#define LOG_PreSmooth                 39      // uint8_t
#define LOG_VocOffset                 40      // int8_t
#define LOG_VocCycle                  41      // int32_t
#define LOG_VocDeltaAbs               45      // uint16_t
#define LOG_VocDeltPercent            47      // uint8_t
#define LOG_VocSmooth                 48      // uint8_t
#define LOG_Co2Offset                 49      // int8_t
#define LOG_Co2Cycle                  50      // int32_t
#define LOG_Co2DeltaAbs               54      // uint16_t
#define LOG_Co2DeltaPercent           56      // uint8_t
#define LOG_Co2Smooth                 57      // uint8_t
#define LOG_SensorDevice              58      // 6 Bits, Bit 6-1
#define LOG_Logic                     58      // 1 Bit, Bit 7
#define LOG_Sensor1Wire               58      // 1 Bit, Bit 0
#define LOG_Dewpoint                  12      // 1 Bit, Bit 6
#define LOG_Comfort                   12      // 1 Bit, Bit 5
#define LOG_DewOffset                 59      // int8_t
#define LOG_DewCycle                  60      // int32_t
#define LOG_DewDeltaAbs               64      // uint16_t
#define LOG_DewDeltaPercent           66      // uint8_t
#define LOG_DewSmooth                 67      // uint8_t

#define LOG_Channels 10

// Parameter per channel
#define LOG_ParamBlockOffset 68
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
#define LOG_fE1Dpt                    10      // 8 Bits, Bit 7-0
#define LOG_fE1Convert                 9      // 4 Bits, Bit 7-4
#define LOG_fE1LowDelta               11      // int32_t
#define LOG_fE1HighDelta              15      // int32_t
#define LOG_fE1LowDpt2                11      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2               12      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2               13      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2               14      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                11      // uint8_t
#define LOG_fE1HighDpt5               15      // uint8_t
#define LOG_fE1LowDpt5001             11      // uint8_t
#define LOG_fE1HighDpt5001            15      // uint8_t
#define LOG_fE1LowDpt6                11      // int8_t
#define LOG_fE1HighDpt6               15      // int8_t
#define LOG_fE1LowDpt7                11      // uint16_t
#define LOG_fE1HighDpt7               15      // uint16_t
#define LOG_fE1LowDpt8                11      // int16_t
#define LOG_fE1HighDpt8               15      // int16_t
#define LOG_fE1LowDpt9                11      // float
#define LOG_fE1HighDpt9               15      // float
#define LOG_fE1Low0Dpt17              11      // uint8_t
#define LOG_fE1Low1Dpt17              12      // uint8_t
#define LOG_fE1Low2Dpt17              13      // uint8_t
#define LOG_fE1Low3Dpt17              14      // uint8_t
#define LOG_fE1Low4Dpt17              15      // uint8_t
#define LOG_fE1Low5Dpt17              16      // uint8_t
#define LOG_fE1Low6Dpt17              17      // uint8_t
#define LOG_fE1Low7Dpt17              18      // uint8_t
#define LOG_fE1LowDptRGB              11      // int32_t
#define LOG_fE1HighDptRGB             15      // int32_t
#define LOG_fE1Default                19      // 8 Bits, Bit 7-0
#define LOG_fE1Repeat                 20      // int32_t
#define LOG_fE2                       24      // 4 Bits, Bit 3-0
#define LOG_fE2Dpt                    25      // 8 Bits, Bit 7-0
#define LOG_fE2Convert                24      // 4 Bits, Bit 7-4
#define LOG_fE2Low0Dpt2               26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2               27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2               28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2               29      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                26      // uint8_t
#define LOG_fE2HighDpt5               30      // uint8_t
#define LOG_fE2LowDpt5001             26      // uint8_t
#define LOG_fE2HighDpt5001            30      // uint8_t
#define LOG_fE2LowDpt6                26      // int8_t
#define LOG_fE2HighDpt6               30      // int8_t
#define LOG_fE2LowDpt7                26      // uint16_t
#define LOG_fE2HighDpt7               30      // uint16_t
#define LOG_fE2LowDpt8                26      // int16_t
#define LOG_fE2HighDpt8               30      // int16_t
#define LOG_fE2LowDpt9                26      // float
#define LOG_fE2HighDpt9               30      // float
#define LOG_fE2Low0Dpt17              26      // uint8_t
#define LOG_fE2Low1Dpt17              27      // uint8_t
#define LOG_fE2Low2Dpt17              28      // uint8_t
#define LOG_fE2Low3Dpt17              29      // uint8_t
#define LOG_fE2Low4Dpt17              30      // uint8_t
#define LOG_fE2Low5Dpt17              31      // uint8_t
#define LOG_fE2Low6Dpt17              32      // uint8_t
#define LOG_fE2Low7Dpt17              33      // uint8_t
#define LOG_fE2LowDptRGB              26      // int32_t
#define LOG_fE2HighDptRGB             30      // int32_t
#define LOG_fE2Default                34      // 8 Bits, Bit 7-0
#define LOG_fE2Repeat                 35      // int32_t
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
#define LOG_fODelayOn                 62      // int32_t
#define LOG_fODelayOnRepeat           61      // 2 Bits, Bit 6-5
#define LOG_fODelayOnReset            61      // 1 Bit, Bit 4
#define LOG_fODelayOff                66      // int32_t
#define LOG_fODelayOffRepeat          61      // 2 Bits, Bit 3-2
#define LOG_fODelayOffReset           61      // 1 Bit, Bit 1
#define LOG_fORepeat                  70      // 1 Bit, Bit 7
#define LOG_fORepeatOn                71      // int32_t
#define LOG_fORepeatOff               75      // int32_t
#define LOG_fOOutputFilter            70      // 2 Bits, Bit 6-5
#define LOG_fODpt                     79      // 8 Bits, Bit 7-0
#define LOG_fOOn                      80      // 8 Bits, Bit 7-0
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
#define LOG_fOOnRGB                   81      // int32_t
#define LOG_fOOnPAArea                81      // 4 Bits, Bit 7-4
#define LOG_fOOnPALine                81      // 4 Bits, Bit 3-0
#define LOG_fOOnPADevice              82      // uint8_t
#define LOG_fOOff                     95      // 8 Bits, Bit 7-0
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
#define LOG_fOOffRGB                  96      // int32_t
#define LOG_fOOffPAArea               96      // 4 Bits, Bit 7-4
#define LOG_fOOffPALine               96      // 4 Bits, Bit 3-0
#define LOG_fOOffPADevice             97      // uint8_t

// Communication objects per channel (multiple occurance)
#define LOG_KoOffset 30
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Communication objects with single occurance
#define LOG_KoHeartbeat 1
#define LOG_KoError 2
#define LOG_KoTemp 5
#define LOG_KoHum 6
#define LOG_KoPre 7
#define LOG_KoVOC 8
#define LOG_KoCo2 9
#define LOG_KoDewpoint 11
#define LOG_KoComfort 12
#define LOG_KoRequestValues 15

