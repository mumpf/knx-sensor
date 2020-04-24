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
#define LOG_VacationKo                 9      // 1 Bit, Bit 2
#define LOG_HolidayKo                  9      // 1 Bit, Bit 1
#define LOG_Neujahr                   10      // 1 Bit, Bit 7
#define LOG_DreiKoenige               10      // 1 Bit, Bit 6
#define LOG_Weiberfastnacht           10      // 1 Bit, Bit 5
#define LOG_Rosenmontag               10      // 1 Bit, Bit 4
#define LOG_Fastnachtsdienstag        10      // 1 Bit, Bit 3
#define LOG_Aschermittwoch            10      // 1 Bit, Bit 2
#define LOG_Gruendonnerstag           10      // 1 Bit, Bit 1
#define LOG_Karfreitag                10      // 1 Bit, Bit 0
#define LOG_Ostersonntag              11      // 1 Bit, Bit 7
#define LOG_Ostermontag               11      // 1 Bit, Bit 6
#define LOG_TagDerArbeit              11      // 1 Bit, Bit 5
#define LOG_Himmelfahrt               11      // 1 Bit, Bit 4
#define LOG_Pfingstsonntag            11      // 1 Bit, Bit 3
#define LOG_Pfingstmontag             11      // 1 Bit, Bit 2
#define LOG_Frohleichnam              11      // 1 Bit, Bit 1
#define LOG_Friedensfest              11      // 1 Bit, Bit 0
#define LOG_MariaHimmelfahrt          12      // 1 Bit, Bit 7
#define LOG_DeutscheEinheit           12      // 1 Bit, Bit 6
#define LOG_Reformationstag           12      // 1 Bit, Bit 5
#define LOG_Allerheiligen             12      // 1 Bit, Bit 4
#define LOG_BussBettag                12      // 1 Bit, Bit 3
#define LOG_Heiligabend               12      // 1 Bit, Bit 2
#define LOG_Weihnachtstag1            12      // 1 Bit, Bit 1
#define LOG_Weihnachtstag2            12      // 1 Bit, Bit 0
#define LOG_Silvester                 13      // 1 Bit, Bit 7
#define LOG_Error                     15      // 1 Bit, Bit 7
#define LOG_Dewpoint                  15      // 1 Bit, Bit 6
#define LOG_Comfort                   15      // 1 Bit, Bit 5
#define LOG_Airquality                15      // 1 Bit, Bit 4
#define LOG_Accuracy                  15      // 1 Bit, Bit 3
#define LOG_DeleteData                15      // 1 Bit, Bit 2
#define LOG_TempOffset                16      // int8_t
#define LOG_TempCycle                 17      // int32_t
#define LOG_TempDeltaAbs              21      // uint16_t
#define LOG_TempDeltaPercent          23      // uint8_t
#define LOG_TempSmooth                24      // uint8_t
#define LOG_TempExtCount              25      // 2 Bits, Bit 1-0
#define LOG_TempExtRead               25      // 1 Bit, Bit 2
#define LOG_TempIntPercent            26      // uint8_t
#define LOG_TempExt1Percent           27      // uint8_t
#define LOG_TempExt2Percent           28      // uint8_t
#define LOG_HumOffset                 29      // int8_t
#define LOG_HumCycle                  30      // int32_t
#define LOG_HumDeltaAbs               34      // uint16_t
#define LOG_HumDeltaPercent           36      // uint8_t
#define LOG_HumSmooth                 37      // uint8_t
#define LOG_HumExtCount               38      // 2 Bits, Bit 1-0
#define LOG_HumExtRead                38      // 1 Bit, Bit 2
#define LOG_HumIntPercent             39      // uint8_t
#define LOG_HumExt1Percent            40      // uint8_t
#define LOG_HumExt2Percent            41      // uint8_t
#define LOG_PreOffset                 42      // int8_t
#define LOG_PreCycle                  43      // int32_t
#define LOG_PreDeltaAbs               47      // uint16_t
#define LOG_PreDeltaPercent           49      // uint8_t
#define LOG_PreSmooth                 50      // uint8_t
#define LOG_PreExtCount               51      // 2 Bits, Bit 1-0
#define LOG_PreExtRead                51      // 1 Bit, Bit 2
#define LOG_PreIntPercent             52      // uint8_t
#define LOG_PreExt1Percent            53      // uint8_t
#define LOG_PreExt2Percent            54      // uint8_t
#define LOG_VocOffset                 55      // int8_t
#define LOG_VocCycle                  56      // int32_t
#define LOG_VocDeltaAbs               60      // uint16_t
#define LOG_VocDeltPercent            62      // uint8_t
#define LOG_VocSmooth                 63      // uint8_t
#define LOG_VocExtCount               64      // 2 Bits, Bit 1-0
#define LOG_VocExtRead                64      // 1 Bit, Bit 2
#define LOG_VocIntPercent             65      // uint8_t
#define LOG_VocExt1Percent            66      // uint8_t
#define LOG_VocExt2Percent            67      // uint8_t
#define LOG_Co2Offset                 68      // int8_t
#define LOG_Co2Cycle                  69      // int32_t
#define LOG_Co2DeltaAbs               73      // uint16_t
#define LOG_Co2DeltaPercent           75      // uint8_t
#define LOG_Co2Smooth                 76      // uint8_t
#define LOG_Co2ExtCount               77      // 2 Bits, Bit 1-0
#define LOG_Co2ExtRead                77      // 1 Bit, Bit 2
#define LOG_Co2IntPercent             78      // uint8_t
#define LOG_Co2Ext1Percent            79      // uint8_t
#define LOG_Co2Ext2Percent            80      // uint8_t
#define LOG_SensorDevice              81      // 6 Bits, Bit 6-1
#define LOG_Sensor1Wire               81      // 1 Bit, Bit 0
#define LOG_DewOffset                 82      // int8_t
#define LOG_DewCycle                  83      // int32_t
#define LOG_DewDeltaAbs               87      // uint16_t
#define LOG_DewDeltaPercent           89      // uint8_t
#define LOG_DewSmooth                 90      // uint8_t

// Parameter per channel
#define LOG_ParamBlockOffset 91
#define LOG_ParamBlockSize 100
#define LOG_fChannelDelay              0      // int32_t
#define LOG_fLogic                     4      // 8 Bits, Bit 7-0
#define LOG_fCalculate                 5      // 2 Bits, Bit 1-0
#define LOG_fDisable                   5      // 1 Bit, Bit 2
#define LOG_fTrigger                   6      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                 6      // 1 Bit, Bit 0
#define LOG_fTriggerE2                 6      // 1 Bit, Bit 1
#define LOG_fTriggerI1                 6      // 1 Bit, Bit 2
#define LOG_fTriggerI2                 6      // 1 Bit, Bit 3
#define LOG_fTriggerTime               6      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose          7      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateOpen           8      // 8 Bits, Bit 7-0
#define LOG_fE1                        9      // 4 Bits, Bit 3-0
#define LOG_fE1Convert                 9      // 4 Bits, Bit 7-4
#define LOG_fE1Dpt                    10      // 8 Bits, Bit 7-0
#define LOG_fE1Default                11      // 2 Bits, Bit 1-0
#define LOG_fE1DefaultEEPROM          11      // 1 Bit, Bit 2
#define LOG_fE1DefaultRepeat          11      // 1 Bit, Bit 3
#define LOG_fTYearDay                 11      // 1 Bit, Bit 4
#define LOG_fTRestoreState            11      // 2 Bits, Bit 6-5
#define LOG_fE1Repeat                 12      // int32_t
#define LOG_fE2                       16      // 4 Bits, Bit 3-0
#define LOG_fE2Convert                16      // 4 Bits, Bit 7-4
#define LOG_fE2Dpt                    17      // 8 Bits, Bit 7-0
#define LOG_fE2Default                18      // 2 Bits, Bit 1-0
#define LOG_fE2DefaultEEPROM          18      // 1 Bit, Bit 2
#define LOG_fE2DefaultRepeat          18      // 1 Bit, Bit 3
#define LOG_fTHoliday                 18      // 2 Bits, Bit 4-3
#define LOG_fTVacation                18      // 2 Bits, Bit 6-5
#define LOG_fE2Repeat                 19      // int32_t
#define LOG_fTd1DuskDawn              19      // 4 Bits, Bit 7-4
#define LOG_fTd2DuskDawn              19      // 4 Bits, Bit 3-0
#define LOG_fTd3DuskDawn              20      // 4 Bits, Bit 7-4
#define LOG_fTd4DuskDawn              20      // 4 Bits, Bit 3-0
#define LOG_fTd5DuskDawn              21      // 4 Bits, Bit 7-4
#define LOG_fTd6DuskDawn              21      // 4 Bits, Bit 3-0
#define LOG_fTd7DuskDawn              22      // 4 Bits, Bit 7-4
#define LOG_fTd8DuskDawn              22      // 4 Bits, Bit 3-0
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
#define LOG_fE1Low0Dpt17              23      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17              24      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17              25      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17              26      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17              27      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17              28      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17              29      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17              30      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB              23      // int32_t
#define LOG_fE1HighDptRGB             27      // int32_t
#define LOG_fE2LowDelta               31      // int32_t
#define LOG_fE2HighDelta              35      // int32_t
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
#define LOG_fE2Low0Dpt17              31      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17              32      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17              33      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17              34      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17              35      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17              36      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17              37      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17              38      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB              31      // int32_t
#define LOG_fE2HighDptRGB             35      // int32_t
#define LOG_fTd1Value                 23      // 1 Bit, Bit 7
#define LOG_fTd1HourAbs               23      // 5 Bits, Bit 5-1
#define LOG_fTd1HourRel               23      // 5 Bits, Bit 5-1
#define LOG_fTd1MinuteAbs             23      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel             23      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday               24      // 3 Bits, Bit 2-0
#define LOG_fTd2Value                 25      // 1 Bit, Bit 7
#define LOG_fTd2HourAbs               25      // 5 Bits, Bit 5-1
#define LOG_fTd2HourRel               25      // 5 Bits, Bit 5-1
#define LOG_fTd2MinuteAbs             25      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel             25      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday               26      // 3 Bits, Bit 2-0
#define LOG_fTd3Value                 27      // 1 Bit, Bit 7
#define LOG_fTd3HourAbs               27      // 5 Bits, Bit 5-1
#define LOG_fTd3HourRel               27      // 5 Bits, Bit 5-1
#define LOG_fTd3MinuteAbs             27      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel             27      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday               28      // 3 Bits, Bit 2-0
#define LOG_fTd4Value                 29      // 1 Bit, Bit 7
#define LOG_fTd4HourAbs               29      // 5 Bits, Bit 5-1
#define LOG_fTd4HourRel               29      // 5 Bits, Bit 5-1
#define LOG_fTd4MinuteAbs             29      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel             29      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday               30      // 3 Bits, Bit 2-0
#define LOG_fTd5Value                 31      // 1 Bit, Bit 7
#define LOG_fTd5HourAbs               31      // 5 Bits, Bit 5-1
#define LOG_fTd5HourRel               31      // 5 Bits, Bit 5-1
#define LOG_fTd5MinuteAbs             31      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel             31      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday               32      // 3 Bits, Bit 2-0
#define LOG_fTd6Value                 33      // 1 Bit, Bit 7
#define LOG_fTd6HourAbs               33      // 5 Bits, Bit 5-1
#define LOG_fTd6HourRel               33      // 5 Bits, Bit 5-1
#define LOG_fTd6MinuteAbs             33      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel             33      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday               34      // 3 Bits, Bit 2-0
#define LOG_fTd7Value                 35      // 1 Bit, Bit 7
#define LOG_fTd7HourAbs               35      // 5 Bits, Bit 5-1
#define LOG_fTd7HourRel               35      // 5 Bits, Bit 5-1
#define LOG_fTd7MinuteAbs             35      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel             35      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday               36      // 3 Bits, Bit 2-0
#define LOG_fTd8Value                 37      // 1 Bit, Bit 7
#define LOG_fTd8HourAbs               37      // 5 Bits, Bit 5-1
#define LOG_fTd8HourRel               37      // 5 Bits, Bit 5-1
#define LOG_fTd8MinuteAbs             37      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel             37      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday               38      // 3 Bits, Bit 2-0
#define LOG_fTy1Weekday1              31      // 1 Bit, Bit 7
#define LOG_fTy1Weekday2              31      // 1 Bit, Bit 6
#define LOG_fTy1Weekday3              31      // 1 Bit, Bit 5
#define LOG_fTy1Weekday4              31      // 1 Bit, Bit 4
#define LOG_fTy1Weekday5              31      // 1 Bit, Bit 3
#define LOG_fTy1Weekday6              31      // 1 Bit, Bit 2
#define LOG_fTy1Weekday7              31      // 1 Bit, Bit 1
#define LOG_fTy1Day                   31      // 7 Bits, Bit 7-1
#define LOG_fTy1IsWeekday             31      // 1 Bit, Bit 0
#define LOG_fTy1Month                 32      // 4 Bits, Bit 7-4
#define LOG_fTy2Weekday1              33      // 1 Bit, Bit 7
#define LOG_fTy2Weekday2              33      // 1 Bit, Bit 6
#define LOG_fTy2Weekday3              33      // 1 Bit, Bit 5
#define LOG_fTy2Weekday4              33      // 1 Bit, Bit 4
#define LOG_fTy2Weekday5              33      // 1 Bit, Bit 3
#define LOG_fTy2Weekday6              33      // 1 Bit, Bit 2
#define LOG_fTy2Weekday7              33      // 1 Bit, Bit 1
#define LOG_fTy2Day                   33      // 7 Bits, Bit 7-1
#define LOG_fTy2IsWeekday             33      // 1 Bit, Bit 0
#define LOG_fTy2Month                 34      // 4 Bits, Bit 7-4
#define LOG_fTy3Weekday1              35      // 1 Bit, Bit 7
#define LOG_fTy3Weekday2              35      // 1 Bit, Bit 6
#define LOG_fTy3Weekday3              35      // 1 Bit, Bit 5
#define LOG_fTy3Weekday4              35      // 1 Bit, Bit 4
#define LOG_fTy3Weekday5              35      // 1 Bit, Bit 3
#define LOG_fTy3Weekday6              35      // 1 Bit, Bit 2
#define LOG_fTy3Weekday7              35      // 1 Bit, Bit 1
#define LOG_fTy3Day                   35      // 7 Bits, Bit 7-1
#define LOG_fTy3IsWeekday             35      // 1 Bit, Bit 0
#define LOG_fTy3Month                 36      // 4 Bits, Bit 7-4
#define LOG_fTy4Weekday1              37      // 1 Bit, Bit 7
#define LOG_fTy4Weekday2              37      // 1 Bit, Bit 6
#define LOG_fTy4Weekday3              37      // 1 Bit, Bit 5
#define LOG_fTy4Weekday4              37      // 1 Bit, Bit 4
#define LOG_fTy4Weekday5              37      // 1 Bit, Bit 3
#define LOG_fTy4Weekday6              37      // 1 Bit, Bit 2
#define LOG_fTy4Weekday7              37      // 1 Bit, Bit 1
#define LOG_fTy4Day                   37      // 7 Bits, Bit 7-1
#define LOG_fTy4IsWeekday             37      // 1 Bit, Bit 0
#define LOG_fTy4Month                 38      // 4 Bits, Bit 7-4
#define LOG_fI1                       39      // 4 Bits, Bit 7-4
#define LOG_fI2                       39      // 4 Bits, Bit 3-0
#define LOG_fI1Function               40      // uint8_t
#define LOG_fI2Function               41      // uint8_t
#define LOG_fOTimeBase                42      // 8 Bits, Bit 7-0
#define LOG_fOTime                    43      // int32_t
#define LOG_fOBlink                   47      // int32_t
#define LOG_fODelay                   51      // 1 Bit, Bit 7
#define LOG_fODelayOnRepeat           51      // 2 Bits, Bit 6-5
#define LOG_fODelayOnReset            51      // 1 Bit, Bit 4
#define LOG_fODelayOffRepeat          51      // 2 Bits, Bit 3-2
#define LOG_fODelayOffReset           51      // 1 Bit, Bit 1
#define LOG_fODelayOn                 52      // int32_t
#define LOG_fODelayOff                56      // int32_t
#define LOG_fOStair                   60      // 1 Bit, Bit 7
#define LOG_fORetrigger               60      // 1 Bit, Bit 6
#define LOG_fOStairOff                60      // 1 Bit, Bit 5
#define LOG_fORepeat                  60      // 1 Bit, Bit 4
#define LOG_fOOutputFilter            60      // 2 Bits, Bit 3-2
#define LOG_fORepeatOn                61      // int32_t
#define LOG_fORepeatOff               65      // int32_t
#define LOG_fODpt                     69      // 8 Bits, Bit 7-0
#define LOG_fOOn                      70      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                70      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                   70      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                   70      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                  71      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                  71      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                  71      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                  71      // uint8_t
#define LOG_fOOnDpt5001               71      // uint8_t
#define LOG_fOOnDpt6                  71      // int8_t
#define LOG_fOOnDpt7                  71      // uint16_t
#define LOG_fOOnDpt8                  71      // int16_t
#define LOG_fOOnDpt9                  71      // float
#define LOG_fOOnDpt16                 71      // char*, 14 Byte
#define LOG_fOOnDpt17                 71      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                   71      // color, uint, 3 Byte
#define LOG_fOOnPAArea                71      // 4 Bits, Bit 7-4
#define LOG_fOOnPALine                71      // 4 Bits, Bit 3-0
#define LOG_fOOnPADevice              72      // uint8_t
#define LOG_fOOff                     85      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer               85      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                  85      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                  85      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                 86      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                 86      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                 86      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                 86      // uint8_t
#define LOG_fOOffDpt5001              86      // uint8_t
#define LOG_fOOffDpt6                 86      // int8_t
#define LOG_fOOffDpt7                 86      // uint16_t
#define LOG_fOOffDpt8                 86      // int16_t
#define LOG_fOOffDpt9                 86      // float
#define LOG_fOOffDpt16                86      // char*, 14 Byte
#define LOG_fOOffDpt17                86      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                  86      // color, uint, 3 Byte
#define LOG_fOOffPAArea               86      // 4 Bits, Bit 7-4
#define LOG_fOOffPALine               86      // 4 Bits, Bit 3-0
#define LOG_fOOffPADevice             87      // uint8_t

// Communication objects per channel (multiple occurance)
#define LOG_KoOffset 50
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Communication objects with single occurance
#define LOG_KoHeartbeat 1
#define LOG_KoTime 2
#define LOG_KoDate 3
#define LOG_KoVacation 4
#define LOG_KoHoliday1 5
#define LOG_KoHoliday2 6
#define LOG_KoRequestValues 10
#define LOG_KoError 11
#define LOG_KoDiagnose 12
#define LOG_KoTemp 15
#define LOG_KoHum 16
#define LOG_KoPre 17
#define LOG_KoVOC 18
#define LOG_KoCo2 19
#define LOG_KoCo2b 20
#define LOG_KoDewpoint 21
#define LOG_KoComfort 22
#define LOG_KoAirquality 23
#define LOG_KoSensorAccuracy 24
#define LOG_KoExt1Temp 30
#define LOG_KoExt2Temp 31
#define LOG_KoExt1Hum 32
#define LOG_KoExt2Hum 33
#define LOG_KoExt1Pre 34
#define LOG_KoExt2Pre 35
#define LOG_KoExt1VOC 36
#define LOG_KoExt2VOC 37
#define LOG_KoExt1Co2 38
#define LOG_KoExt2Co2 39

