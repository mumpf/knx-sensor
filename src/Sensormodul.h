#pragma once
#include <knx.h>

// Parameter with single occurance
#define LOG_NumChannels                0      // uint8_t
#define LOG_StartupDelay               1      // int32_t
#define LOG_Heartbeat                  5      // int32_t
#define LOG_ReadTimeDate               9      // 1 Bit, Bit 7
#define     LOG_ReadTimeDateMask 0x80
#define     LOG_ReadTimeDateShift 7
#define LOG_BuzzerInstalled            9      // 1 Bit, Bit 6
#define     LOG_BuzzerInstalledMask 0x40
#define     LOG_BuzzerInstalledShift 6
#define LOG_LedInstalled               9      // 1 Bit, Bit 5
#define     LOG_LedInstalledMask 0x20
#define     LOG_LedInstalledShift 5
#define LOG_EepromInstalled            9      // 1 Bit, Bit 4
#define     LOG_EepromInstalledMask 0x10
#define     LOG_EepromInstalledShift 4
#define LOG_NCN5130Installed           9      // 1 Bit, Bit 3
#define     LOG_NCN5130InstalledMask 0x08
#define     LOG_NCN5130InstalledShift 3
#define LOG_VacationKo                 9      // 1 Bit, Bit 2
#define     LOG_VacationKoMask 0x04
#define     LOG_VacationKoShift 2
#define LOG_HolidayKo                  9      // 1 Bit, Bit 1
#define     LOG_HolidayKoMask 0x02
#define     LOG_HolidayKoShift 1
#define LOG_VacationRead               9      // 1 Bit, Bit 0
#define     LOG_VacationReadMask 0x01
#define     LOG_VacationReadShift 0
#define LOG_HolidaySend               10      // 1 Bit, Bit 7
#define     LOG_HolidaySendMask 0x80
#define     LOG_HolidaySendShift 7
#define LOG_Timezone                  10      // 2 Bits, Bit 6-5
#define     LOG_TimezoneMask 0x60
#define     LOG_TimezoneShift 5
#define LOG_UseSummertime             10      // 1 Bit, Bit 4
#define     LOG_UseSummertimeMask 0x10
#define     LOG_UseSummertimeShift 4
#define LOG_Diagnose                  10      // 1 Bit, Bit 3
#define     LOG_DiagnoseMask 0x08
#define     LOG_DiagnoseShift 3
#define LOG_Watchdog                  10      // 1 Bit, Bit 2
#define     LOG_WatchdogMask 0x04
#define     LOG_WatchdogShift 2
#define LOG_Neujahr                   11      // 1 Bit, Bit 7
#define     LOG_NeujahrMask 0x80
#define     LOG_NeujahrShift 7
#define LOG_DreiKoenige               11      // 1 Bit, Bit 6
#define     LOG_DreiKoenigeMask 0x40
#define     LOG_DreiKoenigeShift 6
#define LOG_Weiberfastnacht           11      // 1 Bit, Bit 5
#define     LOG_WeiberfastnachtMask 0x20
#define     LOG_WeiberfastnachtShift 5
#define LOG_Rosenmontag               11      // 1 Bit, Bit 4
#define     LOG_RosenmontagMask 0x10
#define     LOG_RosenmontagShift 4
#define LOG_Fastnachtsdienstag        11      // 1 Bit, Bit 3
#define     LOG_FastnachtsdienstagMask 0x08
#define     LOG_FastnachtsdienstagShift 3
#define LOG_Aschermittwoch            11      // 1 Bit, Bit 2
#define     LOG_AschermittwochMask 0x04
#define     LOG_AschermittwochShift 2
#define LOG_Gruendonnerstag           11      // 1 Bit, Bit 1
#define     LOG_GruendonnerstagMask 0x02
#define     LOG_GruendonnerstagShift 1
#define LOG_Karfreitag                11      // 1 Bit, Bit 0
#define     LOG_KarfreitagMask 0x01
#define     LOG_KarfreitagShift 0
#define LOG_Ostersonntag              12      // 1 Bit, Bit 7
#define     LOG_OstersonntagMask 0x80
#define     LOG_OstersonntagShift 7
#define LOG_Ostermontag               12      // 1 Bit, Bit 6
#define     LOG_OstermontagMask 0x40
#define     LOG_OstermontagShift 6
#define LOG_TagDerArbeit              12      // 1 Bit, Bit 5
#define     LOG_TagDerArbeitMask 0x20
#define     LOG_TagDerArbeitShift 5
#define LOG_Himmelfahrt               12      // 1 Bit, Bit 4
#define     LOG_HimmelfahrtMask 0x10
#define     LOG_HimmelfahrtShift 4
#define LOG_Pfingstsonntag            12      // 1 Bit, Bit 3
#define     LOG_PfingstsonntagMask 0x08
#define     LOG_PfingstsonntagShift 3
#define LOG_Pfingstmontag             12      // 1 Bit, Bit 2
#define     LOG_PfingstmontagMask 0x04
#define     LOG_PfingstmontagShift 2
#define LOG_Frohleichnam              12      // 1 Bit, Bit 1
#define     LOG_FrohleichnamMask 0x02
#define     LOG_FrohleichnamShift 1
#define LOG_Friedensfest              12      // 1 Bit, Bit 0
#define     LOG_FriedensfestMask 0x01
#define     LOG_FriedensfestShift 0
#define LOG_MariaHimmelfahrt          13      // 1 Bit, Bit 7
#define     LOG_MariaHimmelfahrtMask 0x80
#define     LOG_MariaHimmelfahrtShift 7
#define LOG_DeutscheEinheit           13      // 1 Bit, Bit 6
#define     LOG_DeutscheEinheitMask 0x40
#define     LOG_DeutscheEinheitShift 6
#define LOG_Reformationstag           13      // 1 Bit, Bit 5
#define     LOG_ReformationstagMask 0x20
#define     LOG_ReformationstagShift 5
#define LOG_Allerheiligen             13      // 1 Bit, Bit 4
#define     LOG_AllerheiligenMask 0x10
#define     LOG_AllerheiligenShift 4
#define LOG_BussBettag                13      // 1 Bit, Bit 3
#define     LOG_BussBettagMask 0x08
#define     LOG_BussBettagShift 3
#define LOG_Advent1                   13      // 1 Bit, Bit 2
#define     LOG_Advent1Mask 0x04
#define     LOG_Advent1Shift 2
#define LOG_Advent2                   13      // 1 Bit, Bit 1
#define     LOG_Advent2Mask 0x02
#define     LOG_Advent2Shift 1
#define LOG_Advent3                   13      // 1 Bit, Bit 0
#define     LOG_Advent3Mask 0x01
#define     LOG_Advent3Shift 0
#define LOG_Advent4                   14      // 1 Bit, Bit 7
#define     LOG_Advent4Mask 0x80
#define     LOG_Advent4Shift 7
#define LOG_Heiligabend               14      // 1 Bit, Bit 6
#define     LOG_HeiligabendMask 0x40
#define     LOG_HeiligabendShift 6
#define LOG_Weihnachtstag1            14      // 1 Bit, Bit 5
#define     LOG_Weihnachtstag1Mask 0x20
#define     LOG_Weihnachtstag1Shift 5
#define LOG_Weihnachtstag2            14      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag2Mask 0x10
#define     LOG_Weihnachtstag2Shift 4
#define LOG_Silvester                 14      // 1 Bit, Bit 3
#define     LOG_SilvesterMask 0x08
#define     LOG_SilvesterShift 3
#define LOG_Latitude                  15      // float
#define LOG_Longitude                 19      // float
#define LOG_WireError                 25      // 1 Bit, Bit 7
#define     LOG_WireErrorMask 0x80
#define     LOG_WireErrorShift 7
#define LOG_BusMasterCount            25      // 2 Bits, Bit 6-5
#define     LOG_BusMasterCountMask 0x60
#define     LOG_BusMasterCountShift 5
#define LOG_IdSearch                  25      // 1 Bit, Bit 4
#define     LOG_IdSearchMask 0x10
#define     LOG_IdSearchShift 4
#define LOG_IButton1                  25      // 1 Bit, Bit 3
#define     LOG_IButton1Mask 0x08
#define     LOG_IButton1Shift 3
#define LOG_IButton2                  25      // 1 Bit, Bit 2
#define     LOG_IButton2Mask 0x04
#define     LOG_IButton2Shift 2
#define LOG_IButton3                  25      // 1 Bit, Bit 1
#define     LOG_IButton3Mask 0x02
#define     LOG_IButton3Shift 1
#define LOG_Group1                    26      // 1 Bit, Bit 7
#define     LOG_Group1Mask 0x80
#define     LOG_Group1Shift 7
#define LOG_Group2                    26      // 1 Bit, Bit 6
#define     LOG_Group2Mask 0x40
#define     LOG_Group2Shift 6
#define LOG_Group3                    26      // 1 Bit, Bit 5
#define     LOG_Group3Mask 0x20
#define     LOG_Group3Shift 5
#define LOG_Group4                    26      // 1 Bit, Bit 4
#define     LOG_Group4Mask 0x10
#define     LOG_Group4Shift 4
#define LOG_Group5                    26      // 1 Bit, Bit 3
#define     LOG_Group5Mask 0x08
#define     LOG_Group5Shift 3
#define LOG_Group6                    26      // 1 Bit, Bit 2
#define     LOG_Group6Mask 0x04
#define     LOG_Group6Shift 2
#define LOG_Group7                    26      // 1 Bit, Bit 1
#define     LOG_Group7Mask 0x02
#define     LOG_Group7Shift 1
#define LOG_Group8                    26      // 1 Bit, Bit 0
#define     LOG_Group8Mask 0x01
#define     LOG_Group8Shift 0
#define LOG_Busmaster1RSTL            27      // 4 Bits, Bit 7-4
#define     LOG_Busmaster1RSTLMask 0xF0
#define     LOG_Busmaster1RSTLShift 4
#define LOG_Busmaster2RSTL            27      // 4 Bits, Bit 3-0
#define     LOG_Busmaster2RSTLMask 0x0F
#define     LOG_Busmaster2RSTLShift 0
#define LOG_Busmaster3RSTL            28      // 4 Bits, Bit 7-4
#define     LOG_Busmaster3RSTLMask 0xF0
#define     LOG_Busmaster3RSTLShift 4
#define LOG_Busmaster4RSTL            28      // 4 Bits, Bit 3-0
#define     LOG_Busmaster4RSTLMask 0x0F
#define     LOG_Busmaster4RSTLShift 0
#define LOG_Busmaster1MSP             29      // 4 Bits, Bit 7-4
#define     LOG_Busmaster1MSPMask 0xF0
#define     LOG_Busmaster1MSPShift 4
#define LOG_Busmaster2MSP             29      // 4 Bits, Bit 3-0
#define     LOG_Busmaster2MSPMask 0x0F
#define     LOG_Busmaster2MSPShift 0
#define LOG_Busmaster3MSP             30      // 4 Bits, Bit 7-4
#define     LOG_Busmaster3MSPMask 0xF0
#define     LOG_Busmaster3MSPShift 4
#define LOG_Busmaster4MSP             30      // 4 Bits, Bit 3-0
#define     LOG_Busmaster4MSPMask 0x0F
#define     LOG_Busmaster4MSPShift 0
#define LOG_Busmaster1W0L             31      // 4 Bits, Bit 7-4
#define     LOG_Busmaster1W0LMask 0xF0
#define     LOG_Busmaster1W0LShift 4
#define LOG_Busmaster2W0L             31      // 4 Bits, Bit 3-0
#define     LOG_Busmaster2W0LMask 0x0F
#define     LOG_Busmaster2W0LShift 0
#define LOG_Busmaster3W0L             32      // 4 Bits, Bit 7-4
#define     LOG_Busmaster3W0LMask 0xF0
#define     LOG_Busmaster3W0LShift 4
#define LOG_Busmaster4W0L             32      // 4 Bits, Bit 3-0
#define     LOG_Busmaster4W0LMask 0x0F
#define     LOG_Busmaster4W0LShift 0
#define LOG_Busmaster1REC0            33      // 4 Bits, Bit 7-4
#define     LOG_Busmaster1REC0Mask 0xF0
#define     LOG_Busmaster1REC0Shift 4
#define LOG_Busmaster2REC0            33      // 4 Bits, Bit 3-0
#define     LOG_Busmaster2REC0Mask 0x0F
#define     LOG_Busmaster2REC0Shift 0
#define LOG_Busmaster3REC0            34      // 4 Bits, Bit 7-4
#define     LOG_Busmaster3REC0Mask 0xF0
#define     LOG_Busmaster3REC0Shift 4
#define LOG_Busmaster4REC0            34      // 4 Bits, Bit 3-0
#define     LOG_Busmaster4REC0Mask 0x0F
#define     LOG_Busmaster4REC0Shift 0
#define LOG_Busmaster1WPU             35      // 4 Bits, Bit 7-4
#define     LOG_Busmaster1WPUMask 0xF0
#define     LOG_Busmaster1WPUShift 4
#define LOG_Busmaster2WPU             35      // 4 Bits, Bit 3-0
#define     LOG_Busmaster2WPUMask 0x0F
#define     LOG_Busmaster2WPUShift 0
#define LOG_Busmaster3WPU             36      // 4 Bits, Bit 7-4
#define     LOG_Busmaster3WPUMask 0xF0
#define     LOG_Busmaster3WPUShift 4
#define LOG_Busmaster4WPU             36      // 4 Bits, Bit 3-0
#define     LOG_Busmaster4WPUMask 0x0F
#define     LOG_Busmaster4WPUShift 0
#define LOG_Error                     35      // 1 Bit, Bit 7
#define     LOG_ErrorMask 0x80
#define     LOG_ErrorShift 7
#define LOG_Dewpoint                  35      // 1 Bit, Bit 6
#define     LOG_DewpointMask 0x40
#define     LOG_DewpointShift 6
#define LOG_Comfort                   35      // 1 Bit, Bit 5
#define     LOG_ComfortMask 0x20
#define     LOG_ComfortShift 5
#define LOG_Airquality                35      // 1 Bit, Bit 4
#define     LOG_AirqualityMask 0x10
#define     LOG_AirqualityShift 4
#define LOG_Accuracy                  35      // 1 Bit, Bit 3
#define     LOG_AccuracyMask 0x08
#define     LOG_AccuracyShift 3
#define LOG_DeleteData                35      // 1 Bit, Bit 2
#define     LOG_DeleteDataMask 0x04
#define     LOG_DeleteDataShift 2
#define LOG_TempOffset                36      // int8_t
#define LOG_TempCycle                 37      // int32_t
#define LOG_TempDeltaAbs              41      // uint16_t
#define LOG_TempDeltaPercent          43      // uint8_t
#define LOG_TempSmooth                44      // uint8_t
#define LOG_TempExtCount              45      // 2 Bits, Bit 1-0
#define     LOG_TempExtCountMask 0x03
#define     LOG_TempExtCountShift 0
#define LOG_TempExtRead               45      // 1 Bit, Bit 2
#define     LOG_TempExtReadMask 0x04
#define     LOG_TempExtReadShift 2
#define LOG_TempIntPercent            46      // uint8_t
#define LOG_TempExt1Percent           47      // uint8_t
#define LOG_TempExt2Percent           48      // uint8_t
#define LOG_HumOffset                 49      // int8_t
#define LOG_HumCycle                  50      // int32_t
#define LOG_HumDeltaAbs               54      // uint16_t
#define LOG_HumDeltaPercent           56      // uint8_t
#define LOG_HumSmooth                 57      // uint8_t
#define LOG_HumExtCount               58      // 2 Bits, Bit 1-0
#define     LOG_HumExtCountMask 0x03
#define     LOG_HumExtCountShift 0
#define LOG_HumExtRead                58      // 1 Bit, Bit 2
#define     LOG_HumExtReadMask 0x04
#define     LOG_HumExtReadShift 2
#define LOG_HumIntPercent             59      // uint8_t
#define LOG_HumExt1Percent            60      // uint8_t
#define LOG_HumExt2Percent            61      // uint8_t
#define LOG_PreOffset                 62      // int8_t
#define LOG_PreCycle                  63      // int32_t
#define LOG_PreDeltaAbs               67      // uint16_t
#define LOG_PreDeltaPercent           69      // uint8_t
#define LOG_PreSmooth                 70      // uint8_t
#define LOG_PreExtCount               71      // 2 Bits, Bit 1-0
#define     LOG_PreExtCountMask 0x03
#define     LOG_PreExtCountShift 0
#define LOG_PreExtRead                71      // 1 Bit, Bit 2
#define     LOG_PreExtReadMask 0x04
#define     LOG_PreExtReadShift 2
#define LOG_PreIntPercent             72      // uint8_t
#define LOG_PreExt1Percent            73      // uint8_t
#define LOG_PreExt2Percent            74      // uint8_t
#define LOG_VocOffset                 75      // int8_t
#define LOG_VocCycle                  76      // int32_t
#define LOG_VocDeltaAbs               80      // uint16_t
#define LOG_VocDeltPercent            82      // uint8_t
#define LOG_VocSmooth                 83      // uint8_t
#define LOG_VocExtCount               84      // 2 Bits, Bit 1-0
#define     LOG_VocExtCountMask 0x03
#define     LOG_VocExtCountShift 0
#define LOG_VocExtRead                84      // 1 Bit, Bit 2
#define     LOG_VocExtReadMask 0x04
#define     LOG_VocExtReadShift 2
#define LOG_VocIntPercent             85      // uint8_t
#define LOG_VocExt1Percent            86      // uint8_t
#define LOG_VocExt2Percent            87      // uint8_t
#define LOG_Co2Offset                 88      // int8_t
#define LOG_Co2Cycle                  89      // int32_t
#define LOG_Co2DeltaAbs               93      // uint16_t
#define LOG_Co2DeltaPercent           95      // uint8_t
#define LOG_Co2Smooth                 96      // uint8_t
#define LOG_Co2ExtCount               97      // 2 Bits, Bit 1-0
#define     LOG_Co2ExtCountMask 0x03
#define     LOG_Co2ExtCountShift 0
#define LOG_Co2ExtRead                97      // 1 Bit, Bit 2
#define     LOG_Co2ExtReadMask 0x04
#define     LOG_Co2ExtReadShift 2
#define LOG_Co2IntPercent             98      // uint8_t
#define LOG_Co2Ext1Percent            99      // uint8_t
#define LOG_Co2Ext2Percent            100      // uint8_t
#define LOG_SensorDevice              101      // 6 Bits, Bit 6-1
#define     LOG_SensorDeviceMask 0x7E
#define     LOG_SensorDeviceShift 1
#define LOG_Sensor1Wire               101      // 1 Bit, Bit 0
#define     LOG_Sensor1WireMask 0x01
#define     LOG_Sensor1WireShift 0
#define LOG_DewOffset                 102      // int8_t
#define LOG_DewCycle                  103      // int32_t
#define LOG_DewDeltaAbs               107      // uint16_t
#define LOG_DewDeltaPercent           109      // uint8_t
#define LOG_DewSmooth                 110      // uint8_t
#define LOG_LuxOffset                 111      // int8_t
#define LOG_LuxCycle                  112      // int32_t
#define LOG_LuxDeltaAbs               116      // uint16_t
#define LOG_LuxDeltPercent            118      // uint8_t
#define LOG_LuxSmooth                 119      // uint8_t
#define LOG_LuxExtCount               120      // 2 Bits, Bit 1-0
#define     LOG_LuxExtCountMask 0x03
#define     LOG_LuxExtCountShift 0
#define LOG_LuxExtRead                120      // 1 Bit, Bit 2
#define     LOG_LuxExtReadMask 0x04
#define     LOG_LuxExtReadShift 2
#define LOG_LuxIntPercent             121      // uint8_t
#define LOG_LuxExt1Percent            122      // uint8_t
#define LOG_LuxExt2Percent            123      // uint8_t
#define LOG_TofOffset                 124      // int8_t
#define LOG_TofCycle                  125      // int32_t
#define LOG_TofDeltaAbs               129      // uint16_t
#define LOG_TofDeltaPercent           131      // uint8_t
#define LOG_TofSmooth                 132      // uint8_t
#define LOG_TofExtCount               133      // 2 Bits, Bit 1-0
#define     LOG_TofExtCountMask 0x03
#define     LOG_TofExtCountShift 0
#define LOG_TofExtRead                133      // 1 Bit, Bit 2
#define     LOG_TofExtReadMask 0x04
#define     LOG_TofExtReadShift 2
#define LOG_TofIntPercent             134      // uint8_t
#define LOG_TofExt1Percent            135      // uint8_t
#define LOG_TofExt2Percent            136      // uint8_t
#define LOG_TempSensor                137      // 4 Bits, Bit 7-4
#define     LOG_TempSensorMask 0xF0
#define     LOG_TempSensorShift 4
#define LOG_HumSensor                 137      // 4 Bits, Bit 3-0
#define     LOG_HumSensorMask 0x0F
#define     LOG_HumSensorShift 0
#define LOG_PreSensor                 138      // 4 Bits, Bit 7-4
#define     LOG_PreSensorMask 0xF0
#define     LOG_PreSensorShift 4
#define LOG_VocSensor                 138      // 4 Bits, Bit 3-0
#define     LOG_VocSensorMask 0x0F
#define     LOG_VocSensorShift 0
#define LOG_Co2Sensor                 139      // 4 Bits, Bit 7-4
#define     LOG_Co2SensorMask 0xF0
#define     LOG_Co2SensorShift 4
#define LOG_LuxSensor                 139      // 4 Bits, Bit 3-0
#define     LOG_LuxSensorMask 0x0F
#define     LOG_LuxSensorShift 0
#define LOG_TofSensor                 140      // 4 Bits, Bit 7-4
#define     LOG_TofSensorMask 0xF0
#define     LOG_TofSensorShift 4

// Parameter per channel
#define LOG_ParamBlockOffset 141
#define LOG_ParamBlockSize 100
#define LOG_fChannelDelay              0      // int32_t
#define LOG_fLogic                     4      // 8 Bits, Bit 7-0
#define LOG_fCalculate                 5      // 2 Bits, Bit 1-0
#define     LOG_fCalculateMask 0x03
#define     LOG_fCalculateShift 0
#define LOG_fDisable                   5      // 1 Bit, Bit 2
#define     LOG_fDisableMask 0x04
#define     LOG_fDisableShift 2
#define LOG_fAlarm                     5      // 1 Bit, Bit 3
#define     LOG_fAlarmMask 0x08
#define     LOG_fAlarmShift 3
#define LOG_fTrigger                   6      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                 6      // 1 Bit, Bit 0
#define     LOG_fTriggerE1Mask 0x01
#define     LOG_fTriggerE1Shift 0
#define LOG_fTriggerE2                 6      // 1 Bit, Bit 1
#define     LOG_fTriggerE2Mask 0x02
#define     LOG_fTriggerE2Shift 1
#define LOG_fTriggerI1                 6      // 1 Bit, Bit 2
#define     LOG_fTriggerI1Mask 0x04
#define     LOG_fTriggerI1Shift 2
#define LOG_fTriggerI2                 6      // 1 Bit, Bit 3
#define     LOG_fTriggerI2Mask 0x08
#define     LOG_fTriggerI2Shift 3
#define LOG_fTriggerTime               6      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose          7      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateOpen           8      // 8 Bits, Bit 7-0
#define LOG_fE1                        9      // 4 Bits, Bit 3-0
#define     LOG_fE1Mask 0x0F
#define     LOG_fE1Shift 0
#define LOG_fE1Convert                 9      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1Dpt                    10      // 8 Bits, Bit 7-0
#define LOG_fE1Default                11      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultEEPROM          11      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat          11      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fTYearDay                 11      // 1 Bit, Bit 4
#define     LOG_fTYearDayMask 0x10
#define     LOG_fTYearDayShift 4
#define LOG_fTRestoreState            11      // 2 Bits, Bit 6-5
#define     LOG_fTRestoreStateMask 0x60
#define     LOG_fTRestoreStateShift 5
#define LOG_fE1Repeat                 12      // int32_t
#define LOG_fE2                       16      // 4 Bits, Bit 3-0
#define     LOG_fE2Mask 0x0F
#define     LOG_fE2Shift 0
#define LOG_fE2Convert                16      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2Dpt                    17      // 8 Bits, Bit 7-0
#define LOG_fE2Default                18      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultEEPROM          18      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat          18      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fTHoliday                 18      // 2 Bits, Bit 4-3
#define     LOG_fTHolidayMask 0x18
#define     LOG_fTHolidayShift 3
#define LOG_fTVacation                18      // 2 Bits, Bit 6-5
#define     LOG_fTVacationMask 0x60
#define     LOG_fTVacationShift 5
#define LOG_fE2Repeat                 19      // int32_t
#define LOG_fTd1DuskDawn              19      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn              19      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn              20      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn              20      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn              21      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn              21      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn              22      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn              22      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
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
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1HourAbs               23      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel               23      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1MinuteAbs             23      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel             23      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday               24      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                 25      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2HourAbs               25      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel               25      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2MinuteAbs             25      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel             25      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday               26      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                 27      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3HourAbs               27      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel               27      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3MinuteAbs             27      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel             27      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday               28      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                 29      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4HourAbs               29      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel               29      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4MinuteAbs             29      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel             29      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday               30      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                 31      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5HourAbs               31      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel               31      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5MinuteAbs             31      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel             31      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday               32      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                 33      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6HourAbs               33      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel               33      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6MinuteAbs             33      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel             33      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday               34      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                 35      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7HourAbs               35      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel               35      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7MinuteAbs             35      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel             35      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday               36      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                 37      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8HourAbs               37      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel               37      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8MinuteAbs             37      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel             37      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday               38      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1              31      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2              31      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3              31      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4              31      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5              31      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6              31      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7              31      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                   31      // 7 Bits, Bit 7-1
#define LOG_fTy1IsWeekday             31      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                 32      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1              33      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2              33      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3              33      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4              33      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5              33      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6              33      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7              33      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                   33      // 7 Bits, Bit 7-1
#define LOG_fTy2IsWeekday             33      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                 34      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1              35      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2              35      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3              35      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4              35      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5              35      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6              35      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7              35      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                   35      // 7 Bits, Bit 7-1
#define LOG_fTy3IsWeekday             35      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                 36      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1              37      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2              37      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3              37      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4              37      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5              37      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6              37      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7              37      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                   37      // 7 Bits, Bit 7-1
#define LOG_fTy4IsWeekday             37      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                 38      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                       39      // 4 Bits, Bit 7-4
#define     LOG_fI1Mask 0xF0
#define     LOG_fI1Shift 4
#define LOG_fI2                       39      // 4 Bits, Bit 3-0
#define     LOG_fI2Mask 0x0F
#define     LOG_fI2Shift 0
#define LOG_fI1Function               40      // uint8_t
#define LOG_fI2Function               41      // uint8_t
#define LOG_fOTimeBase                42      // 8 Bits, Bit 7-0
#define LOG_fOTime                    43      // int32_t
#define LOG_fOBlink                   47      // int32_t
#define LOG_fODelay                   51      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat           51      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset            51      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat          51      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset           51      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fODelayOn                 52      // int32_t
#define LOG_fODelayOff                56      // int32_t
#define LOG_fOStair                   60      // 1 Bit, Bit 7
#define     LOG_fOStairMask 0x80
#define     LOG_fOStairShift 7
#define LOG_fORetrigger               60      // 1 Bit, Bit 6
#define     LOG_fORetriggerMask 0x40
#define     LOG_fORetriggerShift 6
#define LOG_fOStairOff                60      // 1 Bit, Bit 5
#define     LOG_fOStairOffMask 0x20
#define     LOG_fOStairOffShift 5
#define LOG_fORepeat                  60      // 1 Bit, Bit 4
#define     LOG_fORepeatMask 0x10
#define     LOG_fORepeatShift 4
#define LOG_fOOutputFilter            60      // 2 Bits, Bit 3-2
#define     LOG_fOOutputFilterMask 0x0C
#define     LOG_fOOutputFilterShift 2
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
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                71      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
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
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine               86      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice             87      // uint8_t

// Communication objects per channel (multiple occurance)
#define LOG_KoOffset 125
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Parameter per channel
#define WIRE_ParamBlockOffset 8141
#define WIRE_ParamBlockSize 17
#define WIRE_sDeviceId                  0      // char*, 7 Byte
#define WIRE_sFamilyCode                0      // 8 Bits, Bit 7-0
#define WIRE_sId0                       1      // 4 Bits, Bit 7-4
#define     WIRE_sId0Mask 0xF0
#define     WIRE_sId0Shift 4
#define WIRE_sId1                       1      // 4 Bits, Bit 3-0
#define     WIRE_sId1Mask 0x0F
#define     WIRE_sId1Shift 0
#define WIRE_sId2                       2      // 4 Bits, Bit 7-4
#define     WIRE_sId2Mask 0xF0
#define     WIRE_sId2Shift 4
#define WIRE_sId3                       2      // 4 Bits, Bit 3-0
#define     WIRE_sId3Mask 0x0F
#define     WIRE_sId3Shift 0
#define WIRE_sId4                       3      // 4 Bits, Bit 7-4
#define     WIRE_sId4Mask 0xF0
#define     WIRE_sId4Shift 4
#define WIRE_sId5                       3      // 4 Bits, Bit 3-0
#define     WIRE_sId5Mask 0x0F
#define     WIRE_sId5Shift 0
#define WIRE_sId6                       4      // 4 Bits, Bit 7-4
#define     WIRE_sId6Mask 0xF0
#define     WIRE_sId6Shift 4
#define WIRE_sId7                       4      // 4 Bits, Bit 3-0
#define     WIRE_sId7Mask 0x0F
#define     WIRE_sId7Shift 0
#define WIRE_sId8                       5      // 4 Bits, Bit 7-4
#define     WIRE_sId8Mask 0xF0
#define     WIRE_sId8Shift 4
#define WIRE_sId9                       5      // 4 Bits, Bit 3-0
#define     WIRE_sId9Mask 0x0F
#define     WIRE_sId9Shift 0
#define WIRE_sIdA                       6      // 4 Bits, Bit 7-4
#define     WIRE_sIdAMask 0xF0
#define     WIRE_sIdAShift 4
#define WIRE_sIdB                       6      // 4 Bits, Bit 3-0
#define     WIRE_sIdBMask 0x0F
#define     WIRE_sIdBShift 0
#define WIRE_sModelFunction             7      // 8 Bits, Bit 7-0
#define WIRE_sModelFunctionDS2408       7      // 8 Bits, Bit 7-0
#define WIRE_sModelFunctionDS2413       7      // 8 Bits, Bit 7-0
#define WIRE_sModelFunctionDS2438       7      // 8 Bits, Bit 7-0
#define WIRE_sSensorOffset              8      // int8_t
#define WIRE_sSensorCycle               9      // int32_t
#define WIRE_sSensorDeltaAbs           13      // uint16_t
#define WIRE_sSensorDeltaPercent       15      // uint8_t
#define WIRE_sSensorSmooth             16      // uint8_t
#define WIRE_sGroup1                    8      // 1 Bit, Bit 7
#define     WIRE_sGroup1Mask 0x80
#define     WIRE_sGroup1Shift 7
#define WIRE_sGroup2                    8      // 1 Bit, Bit 6
#define     WIRE_sGroup2Mask 0x40
#define     WIRE_sGroup2Shift 6
#define WIRE_sGroup3                    8      // 1 Bit, Bit 5
#define     WIRE_sGroup3Mask 0x20
#define     WIRE_sGroup3Shift 5
#define WIRE_sGroup4                    8      // 1 Bit, Bit 4
#define     WIRE_sGroup4Mask 0x10
#define     WIRE_sGroup4Shift 4
#define WIRE_sGroup5                    8      // 1 Bit, Bit 3
#define     WIRE_sGroup5Mask 0x08
#define     WIRE_sGroup5Shift 3
#define WIRE_sGroup6                    8      // 1 Bit, Bit 2
#define     WIRE_sGroup6Mask 0x04
#define     WIRE_sGroup6Shift 2
#define WIRE_sGroup7                    8      // 1 Bit, Bit 1
#define     WIRE_sGroup7Mask 0x02
#define     WIRE_sGroup7Shift 1
#define WIRE_sGroup8                    8      // 1 Bit, Bit 0
#define     WIRE_sGroup8Mask 0x01
#define     WIRE_sGroup8Shift 0
#define WIRE_sIoBitmask0                8      // 1 Bit, Bit 0
#define     WIRE_sIoBitmask0Mask 0x01
#define     WIRE_sIoBitmask0Shift 0
#define WIRE_sIoBitmask1                8      // 1 Bit, Bit 1
#define     WIRE_sIoBitmask1Mask 0x02
#define     WIRE_sIoBitmask1Shift 1
#define WIRE_sIoBitmask2                8      // 1 Bit, Bit 2
#define     WIRE_sIoBitmask2Mask 0x04
#define     WIRE_sIoBitmask2Shift 2
#define WIRE_sIoBitmask3                8      // 1 Bit, Bit 3
#define     WIRE_sIoBitmask3Mask 0x08
#define     WIRE_sIoBitmask3Shift 3
#define WIRE_sIoBitmask4                8      // 1 Bit, Bit 4
#define     WIRE_sIoBitmask4Mask 0x10
#define     WIRE_sIoBitmask4Shift 4
#define WIRE_sIoBitmask5                8      // 1 Bit, Bit 5
#define     WIRE_sIoBitmask5Mask 0x20
#define     WIRE_sIoBitmask5Shift 5
#define WIRE_sIoBitmask6                8      // 1 Bit, Bit 6
#define     WIRE_sIoBitmask6Mask 0x40
#define     WIRE_sIoBitmask6Shift 6
#define WIRE_sIoBitmask7                8      // 1 Bit, Bit 7
#define     WIRE_sIoBitmask7Mask 0x80
#define     WIRE_sIoBitmask7Shift 7
#define WIRE_sIoInvertBitmask0          9      // 1 Bit, Bit 0
#define     WIRE_sIoInvertBitmask0Mask 0x01
#define     WIRE_sIoInvertBitmask0Shift 0
#define WIRE_sIoInvertBitmask1          9      // 1 Bit, Bit 1
#define     WIRE_sIoInvertBitmask1Mask 0x02
#define     WIRE_sIoInvertBitmask1Shift 1
#define WIRE_sIoInvertBitmask2          9      // 1 Bit, Bit 2
#define     WIRE_sIoInvertBitmask2Mask 0x04
#define     WIRE_sIoInvertBitmask2Shift 2
#define WIRE_sIoInvertBitmask3          9      // 1 Bit, Bit 3
#define     WIRE_sIoInvertBitmask3Mask 0x08
#define     WIRE_sIoInvertBitmask3Shift 3
#define WIRE_sIoInvertBitmask4          9      // 1 Bit, Bit 4
#define     WIRE_sIoInvertBitmask4Mask 0x10
#define     WIRE_sIoInvertBitmask4Shift 4
#define WIRE_sIoInvertBitmask5          9      // 1 Bit, Bit 5
#define     WIRE_sIoInvertBitmask5Mask 0x20
#define     WIRE_sIoInvertBitmask5Shift 5
#define WIRE_sIoInvertBitmask6          9      // 1 Bit, Bit 6
#define     WIRE_sIoInvertBitmask6Mask 0x40
#define     WIRE_sIoInvertBitmask6Shift 6
#define WIRE_sIoInvertBitmask7          9      // 1 Bit, Bit 7
#define     WIRE_sIoInvertBitmask7Mask 0x80
#define     WIRE_sIoInvertBitmask7Shift 7

// Communication objects per channel (multiple occurance)
#define WIRE_KoOffset 90
#define WIRE_KoBlockSize 1
#define WIRE_KoKOs 0

// Communication objects with single occurance
#define LOG_KoHeartbeat 1
#define LOG_KoTime 2
#define LOG_KoDate 3
#define LOG_KoVacation 4
#define LOG_KoHoliday1 5
#define LOG_KoHoliday2 6
#define LOG_KoDiagnose 7
#define LOG_KoLedLock 8
#define LOG_KoBuzzerLock 9
#define LOG_KoNewId 20
#define LOG_KoErrorBusmaster1 21
#define LOG_KoErrorBusmaster2 22
#define LOG_KoErrorBusmaster3 23
#define LOG_KoGroup1 24
#define LOG_KoGroup2 25
#define LOG_KoGroup3 26
#define LOG_KoGroup4 27
#define LOG_KoGroup5 28
#define LOG_KoGroup6 29
#define LOG_KoGroup7 30
#define LOG_KoGroup8 31
#define LOG_KoRequestValues 50
#define LOG_KoError 51
#define LOG_KoTemp 60
#define LOG_KoHum 61
#define LOG_KoPre 62
#define LOG_KoVOC 63
#define LOG_KoCo2 64
#define LOG_KoCo2b 65
#define LOG_KoDewpoint 66
#define LOG_KoComfort 67
#define LOG_KoAirquality 68
#define LOG_KoSensorAccuracy 69
#define LOG_KoExt1Temp 70
#define LOG_KoExt2Temp 71
#define LOG_KoExt1Hum 72
#define LOG_KoExt2Hum 73
#define LOG_KoExt1Pre 74
#define LOG_KoExt2Pre 75
#define LOG_KoExt1VOC 76
#define LOG_KoExt2VOC 77
#define LOG_KoExt1Co2 78
#define LOG_KoExt2Co2 79
#define LOG_KoExt1Lux 80
#define LOG_KoExt2Lux 81
#define LOG_KoExt1Tof 82
#define LOG_KoExt2Tof 83
#define LOG_KoLux 87
#define LOG_KoTof 88

