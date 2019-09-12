#pragma once
#include <knx.h>

// global setup parameters, edit them manually
#define NUM_Channels 40
#define KO_Offset 100

// fixed KO, just one occurence
#define KO_Heartbeat 1
#define KO_Error 2
#define KO_Temp 5
#define KO_Hum 6
#define KO_Pre 7
#define KO_VOC 8
#define KO_Co2 9
#define KO_Dewpoint 11
#define KO_Comfort 12
#define KO_RequestValues 15

// fixed PAR, just one occurence
#define PAR_NumChannels                0      // int32_t
#define PAR_StartupDelay               4      // int32_t
#define PAR_Heartbeat                  8      // int32_t
#define PAR_Error                     12      // 1 Bit, Bit 7
#define PAR_TempOffset                13      // int8_t
#define PAR_TempCycle                 14      // int32_t
#define PAR_TempDeltaAbs              18      // uint16_t
#define PAR_TempDeltaPercent          20      // uint8_t
#define PAR_TempSmooth                21      // uint8_t
#define PAR_HumOffset                 22      // int8_t
#define PAR_HumCycle                  23      // int32_t
#define PAR_HumDeltaAbs               27      // uint16_t
#define PAR_HumDeltaPercent           29      // uint8_t
#define PAR_HumSmooth                 30      // uint8_t
#define PAR_PreOffset                 31      // int8_t
#define PAR_PreCycle                  32      // int32_t
#define PAR_PreDeltaAbs               36      // uint16_t
#define PAR_PreDeltaPercent           38      // uint8_t
#define PAR_PreSmooth                 39      // uint8_t
#define PAR_VocOffset                 40      // int8_t
#define PAR_VocCycle                  41      // int32_t
#define PAR_VocDeltaAbs               45      // uint16_t
#define PAR_VocDeltPercent            47      // uint8_t
#define PAR_VocSmooth                 48      // uint8_t
#define PAR_Co2Offset                 49      // int8_t
#define PAR_Co2Cycle                  50      // int32_t
#define PAR_Co2DeltaAbs               54      // uint16_t
#define PAR_Co2DeltaPercent           56      // uint8_t
#define PAR_Co2Smooth                 57      // uint8_t
#define PAR_SensorDevice              58      // 6 Bits, Bit 6-1
#define PAR_Logic                     58      // 1 Bit, Bit 7
#define PAR_Sensor1Wire               58      // 1 Bit, Bit 0
#define PAR_Dewpoint                  12      // 1 Bit, Bit 6
#define PAR_Comfort                   12      // 1 Bit, Bit 5

// channel PAR, repeated occurence per channel
#define PAR_CH_ChannelDelay            0      // int32_t
#define PAR_CH_Logic                   4      // 8 Bits, Bit 7-0
#define PAR_CH_Calculate               5      // 8 Bits, Bit 7-0
#define PAR_CH_Trigger                 6      // 8 Bits, Bit 7-0
#define PAR_CH_TriggerE1               6      // 1 Bit, Bit 0
#define PAR_CH_TriggerE2               6      // 1 Bit, Bit 1
#define PAR_CH_TriggerI1               6      // 1 Bit, Bit 2
#define PAR_CH_TriggerI2               6      // 1 Bit, Bit 3
#define PAR_CH_TriggerGateClose        7      // 8 Bits, Bit 7-0
#define PAR_CH_TriggerGateOpen         8      // 8 Bits, Bit 7-0
#define PAR_CH_E1                      9      // 4 Bits, Bit 3-0
#define PAR_CH_E1Dpt                  10      // 8 Bits, Bit 7-0
#define PAR_CH_E1Convert               9      // 4 Bits, Bit 7-4
#define PAR_CH_E1LowDelta             11      // int32_t
#define PAR_CH_E1HighDelta            15      // int32_t
#define PAR_CH_E1LowDpt2              11      // 8 Bits, Bit 7-0
#define PAR_CH_E1Low1Dpt2             12      // 8 Bits, Bit 7-0
#define PAR_CH_E1Low2Dpt2             13      // 8 Bits, Bit 7-0
#define PAR_CH_E1Low3Dpt2             14      // 8 Bits, Bit 7-0
#define PAR_CH_E1LowDpt5              11      // uint8_t
#define PAR_CH_E1HighDpt5             15      // uint8_t
#define PAR_CH_E1LowDpt5001           11      // uint8_t
#define PAR_CH_E1HighDpt5001          15      // uint8_t
#define PAR_CH_E1LowDpt6              11      // int8_t
#define PAR_CH_E1HighDpt6             15      // int8_t
#define PAR_CH_E1LowDpt7              11      // uint16_t
#define PAR_CH_E1HighDpt7             15      // uint16_t
#define PAR_CH_E1LowDpt8              11      // int16_t
#define PAR_CH_E1HighDpt8             15      // int16_t
#define PAR_CH_E1LowDpt9              11      // float
#define PAR_CH_E1HighDpt9             15      // float
#define PAR_CH_E1Low0Dpt17            11      // uint8_t
#define PAR_CH_E1Low1Dpt17            12      // uint8_t
#define PAR_CH_E1Low2Dpt17            13      // uint8_t
#define PAR_CH_E1Low3Dpt17            14      // uint8_t
#define PAR_CH_E1Low4Dpt17            15      // uint8_t
#define PAR_CH_E1Low5Dpt17            16      // uint8_t
#define PAR_CH_E1Low6Dpt17            17      // uint8_t
#define PAR_CH_E1Low7Dpt17            18      // uint8_t
#define PAR_CH_E1LowDptRGB            11      // int32_t
#define PAR_CH_E1HighDptRGB           15      // int32_t
#define PAR_CH_E1Default              19      // 8 Bits, Bit 7-0
#define PAR_CH_E1Repeat               20      // int32_t
#define PAR_CH_E2                     24      // 4 Bits, Bit 3-0
#define PAR_CH_E2Dpt                  25      // 8 Bits, Bit 7-0
#define PAR_CH_E2Convert              24      // 4 Bits, Bit 7-4
#define PAR_CH_E2Low0Dpt2             26      // 8 Bits, Bit 7-0
#define PAR_CH_E2Low1Dpt2             27      // 8 Bits, Bit 7-0
#define PAR_CH_E2Low2Dpt2             28      // 8 Bits, Bit 7-0
#define PAR_CH_E2Low3Dpt2             29      // 8 Bits, Bit 7-0
#define PAR_CH_E2LowDpt5              26      // uint8_t
#define PAR_CH_E2HighDpt5             30      // uint8_t
#define PAR_CH_E2LowDpt5001           26      // uint8_t
#define PAR_CH_E2HighDpt5001          30      // uint8_t
#define PAR_CH_E2LowDpt6              26      // int8_t
#define PAR_CH_E2HighDpt6             30      // int8_t
#define PAR_CH_E2LowDpt7              26      // uint16_t
#define PAR_CH_E2HighDpt7             30      // uint16_t
#define PAR_CH_E2LowDpt8              26      // int16_t
#define PAR_CH_E2HighDpt8             30      // int16_t
#define PAR_CH_E2LowDpt9              26      // float
#define PAR_CH_E2HighDpt9             30      // float
#define PAR_CH_E2Low0Dpt17            26      // uint8_t
#define PAR_CH_E2Low1Dpt17            27      // uint8_t
#define PAR_CH_E2Low2Dpt17            28      // uint8_t
#define PAR_CH_E2Low3Dpt17            29      // uint8_t
#define PAR_CH_E2Low4Dpt17            30      // uint8_t
#define PAR_CH_E2Low5Dpt17            31      // uint8_t
#define PAR_CH_E2Low6Dpt17            32      // uint8_t
#define PAR_CH_E2Low7Dpt17            33      // uint8_t
#define PAR_CH_E2LowDptRGB            26      // int32_t
#define PAR_CH_E2HighDptRGB           30      // int32_t
#define PAR_CH_E2Default              34      // 8 Bits, Bit 7-0
#define PAR_CH_E2Repeat               35      // int32_t
#define PAR_CH_I1                     39      // 4 Bits, Bit 7-4
#define PAR_CH_I1Function             40      // int32_t
#define PAR_CH_I2                     44      // 4 Bits, Bit 7-4
#define PAR_CH_I2Function             45      // int32_t
#define PAR_CH_OStair                 49      // 8 Bits, Bit 7-0
#define PAR_CH_OTimeBase              50      // 8 Bits, Bit 7-0
#define PAR_CH_OTime                  51      // int32_t
#define PAR_CH_ORetrigger             55      // 8 Bits, Bit 7-0
#define PAR_CH_OStairOff              56      // 8 Bits, Bit 7-0
#define PAR_CH_OBlink                 57      // int32_t
#define PAR_CH_ODelay                 61      // 1 Bit, Bit 7
#define PAR_CH_ODelayOn               62      // int32_t
#define PAR_CH_ODelayOnRepeat         61      // 2 Bits, Bit 6-5
#define PAR_CH_ODelayOnReset          61      // 1 Bit, Bit 4
#define PAR_CH_ODelayOff              66      // int32_t
#define PAR_CH_ODelayOffRepeat        61      // 2 Bits, Bit 3-2
#define PAR_CH_ODelayOffReset         61      // 1 Bit, Bit 1
#define PAR_CH_ORepeat                70      // 1 Bit, Bit 7
#define PAR_CH_ORepeatOn              71      // int32_t
#define PAR_CH_ORepeatOff             75      // int32_t
#define PAR_CH_OOutputFilter          70      // 2 Bits, Bit 6-5
#define PAR_CH_ODpt                   79      // 8 Bits, Bit 7-0
#define PAR_CH_OOn                    80      // 8 Bits, Bit 7-0
#define PAR_CH_OOnDpt1                81      // 8 Bits, Bit 7-0
#define PAR_CH_OOnDpt2                81      // 8 Bits, Bit 7-0
#define PAR_CH_OOnDpt5                81      // uint8_t
#define PAR_CH_OOnDpt5001             81      // uint8_t
#define PAR_CH_OOnDpt6                81      // int8_t
#define PAR_CH_OOnDpt7                81      // uint16_t
#define PAR_CH_OOnDpt8                81      // int16_t
#define PAR_CH_OOnDpt9                81      // float
#define PAR_CH_OOnDpt16               81      // char*, 14 Byte
#define PAR_CH_OOnDpt17               81      // uint8_t
#define PAR_CH_OOnRGB                 81      // int32_t
#define PAR_CH_OOnPAArea              81      // 4 Bits, Bit 7-4
#define PAR_CH_OOnPALine              81      // 4 Bits, Bit 3-0
#define PAR_CH_OOnPADevice            82      // uint8_t
#define PAR_CH_OOff                   95      // 8 Bits, Bit 7-0
#define PAR_CH_OOffDpt1               96      // 8 Bits, Bit 7-0
#define PAR_CH_OOffDpt2               96      // 8 Bits, Bit 7-0
#define PAR_CH_OOffDpt5               96      // uint8_t
#define PAR_CH_OOffDpt5001            96      // uint8_t
#define PAR_CH_OOffDpt6               96      // int8_t
#define PAR_CH_OOffDpt7               96      // uint16_t
#define PAR_CH_OOffDpt8               96      // int16_t
#define PAR_CH_OOffDpt9               96      // float
#define PAR_CH_OOffDpt16              96      // char*, 14 Byte
#define PAR_CH_OOffDpt17              96      // uint8_t
#define PAR_CH_OOffRGB                96      // int32_t
#define PAR_CH_OOffPAArea             96      // 4 Bits, Bit 7-4
#define PAR_CH_OOffPALine             96      // 4 Bits, Bit 3-0
#define PAR_CH_OOffPADevice           97      // uint8_t

// parameter offset indicators (calculated)
#define NUM_paramOffset 59
#define NUM_paramBlockSize 110
