// ################################################
// ### Debug Print Addr DS18B20
// ################################################

void print_DS18B20_Addr(byte addr[8]) {
  Debug.print(F("%02x%02x%02x%02x%02x%02x%02x%02x  "), addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
}





// ################################################
// ### Setup() Routine
// ################################################

void setup() {

  pinMode(LED_YELLOW, OUTPUT);
  digitalWrite(LED_YELLOW, HIGH);

  // init I2C
  Wire.begin();


  /****************** Init Debug Interface ********************************************/
#ifdef KDEBUG
  // Start debug serial with 9600 bauds
  DEBUGSERIAL.begin(9600);
#if defined(__AVR_ATmega32U4__) || defined(__SAMD21G18A__)
  // wait for serial port to connect. Needed for Leonardo/Micro/ProMicro/Zero only
  while (!DEBUGSERIAL)
#endif
    // make debug serial port known to debug class
    // Means: KONNEKTING will sue the same serial port for console debugging
    Debug.setPrintStream(&DEBUGSERIAL);
  Debug.print(F("KONNEKTING DemoSketch\n"));
#endif




  /******************* check I2C 1-Wire Masters *******************************/
  // 1-WIRE CH3
#ifdef KDEBUG
  Debug.println("*************************************");
  Debug.print("Checking for oneWire_CH3...: ");
#endif
  if (oneWire_CH3.checkPresence())
  {
    CH3_active = true;
    oneWire_CH3.deviceReset();
    oneWire_CH3.setActivePullup();
    if (oneW_CH3_StrongPU_ON)
      oneWire_CH3.setStrongPullup();
#ifdef KDEBUG
    Debug.println("OK");
#endif
  }
  else
  {
#ifdef KDEBUG
    Debug.println("FAIL");
#endif
    CH3_active = false;
  }

  // 1-WIRE CH2
#ifdef KDEBUG
  Debug.println("*************************************");
  Debug.print("Checking for oneWire_CH2...: ");
#endif
  if (oneWire_CH2.checkPresence())
  {
    CH2_active = true;
    oneWire_CH2.deviceReset();
    oneWire_CH2.setActivePullup();
    if (oneW_CH2_StrongPU_ON)
      oneWire_CH2.setStrongPullup();
#ifdef KDEBUG
    Debug.println("OK");
#endif
  }
  else
  {
#ifdef KDEBUG
    Debug.println("FAIL");
#endif
    CH2_active = false;
  }

  // 1-WIRE CH1
#ifdef KDEBUG
  Debug.println("*************************************");
  Debug.print("Checking for oneWire_CH1...: ");
#endif
  if (oneWire_CH1.checkPresence())
  {
    CH1_active = true;
    oneWire_CH1.deviceReset();
    oneWire_CH1.setActivePullup();
    if (oneW_CH1_StrongPU_ON)
      oneWire_CH1.setStrongPullup();
#ifdef KDEBUG
    Debug.println("OK");
#endif
  }
  else
  {
#ifdef KDEBUG
    Debug.println("FAIL");
#endif
    CH1_active = false;
  }

#ifdef KDEBUG
  Debug.println("*************************************");
#endif


  /****************** Init Debug KONNEKTING *******************************************/

  Konnekting.setMemoryReadFunc(&readMemory);
  Konnekting.setMemoryWriteFunc(&writeMemory);
  Konnekting.setMemoryUpdateFunc(&updateMemory);
  Konnekting.setMemoryCommitFunc(&commitMemory);


  // Initialize KNX enabled Arduino Board
  Konnekting.init(KNX_SERIAL, PROG_BUTTON_PIN, PROG_LED_PIN, MANUFACTURER_ID, DEVICE_ID, REVISION);



  /****************** Read Parameter ***************************************************/
#ifdef KDEBUG
  Debug.println("********** READ Parameter ***************************");
#endif

  //  for(int i=0 ; i<1000 ;i++){
  //    writeMemory(i, 255);
  //    delay(5);
  //  }


  if (!Konnekting.isFactorySetting()) {  //check if Device is in Factory-state





    // read the paramters which was defined in the Konnekting Suite
    oneW_CH1_ON                           =            Konnekting.getUINT8Param(PARAM_1WBus1aktiv);                       // 1-Wire CH1 ON/OFF
    oneW_CH2_ON                           =            Konnekting.getUINT8Param(PARAM_1WBus2aktiv);                       // 1-Wire CH2 ON/OFF
    oneW_CH3_ON                           =            Konnekting.getUINT8Param(PARAM_1WBus3aktiv);                       // 1-Wire CH2 ON/OFF

    alive_msg_time                        =            Konnekting.getUINT8Param(PARAM_aliveMSG);                          // ALIVE Counter time

    //Manueles deaktivieren der 1-Wire CH über die Suite
    if (oneW_CH1_ON == false && CH1_active == true)
      CH1_active = false;
    if (oneW_CH2_ON == false && CH2_active == true)
      CH2_active = false;
    if (oneW_CH3_ON == false && CH3_active == true)
      CH3_active = false;

    oneW_CH1_StrongPU_ON                  =            Konnekting.getUINT8Param(PARAM_1Wbus1SPUaktiv);                    // 1-Wire CH1 Strong PulUp ON/OFF
    oneW_CH2_StrongPU_ON                  =            Konnekting.getUINT8Param(PARAM_1Wbus2SPUaktiv);                    // 1-Wire CH2 Strong PulUp ON/OFF
    oneW_CH3_StrongPU_ON                  =            Konnekting.getUINT8Param(PARAM_1Wbus3SPUaktiv);                    // 1-Wire CH2 Strong PulUp ON/OFF

    //new ID
    static uint8_t Interval_sent_new_ID  = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitZyklischesSendenID));           // interval send new Sensor ID
    readNewID                            = ((uint8_t) Konnekting.getUINT8Param(PARAM_einlesenID));                       // read new Sensor ID ON/OFF
    readNewID_bus                        = ((uint8_t) Konnekting.getUINT8Param(PARAM_NewID_Bus));                        // read new Sensor ID BUS



    //DS18B20
    static uint8_t Interval_sent_TvalueCH1 = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitZyklischesSendenTempSensorCH1));      // interval send Temp values
    static uint8_t Interval_sent_TvalueCH2 = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitZyklischesSendenTempSensorCH2));      // interval send Temp values
    static uint8_t Interval_sent_TvalueCH3 = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitZyklischesSendenTempSensorCH3));      // interval send Temp values
    static uint8_t Interval_sent_aenderung_TvalueCH1 = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitSprungSendenTempSensorCH1));      // interval send Temp values bei Wertänderung
    static uint8_t Interval_sent_aenderung_TvalueCH2 = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitSprungSendenTempSensorCH2));      // interval send Temp values bei Wertänderung
    static uint8_t Interval_sent_aenderung_TvalueCH3 = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitSprungSendenTempSensorCH3));      // interval send Temp values bei Wertänderung
    TempResolution_CH1                  =            Konnekting.getUINT8Param(PARAM_TempResolutionCH1);                       // sensor resolution 9bit - 12bit
    TempResolution_CH2                  =            Konnekting.getUINT8Param(PARAM_TempResolutionCH2);                       // sensor resolution 9bit - 12bit
    TempResolution_CH3                  =            Konnekting.getUINT8Param(PARAM_TempResolutionCH3);                       // sensor resolution 9bit - 12bit

    for (int i = 0 ; i < 3 ; i++) {
      Alarm_1_HT[i] =            Konnekting.getUINT8Param(PARAM_CH1_Alarm1toH     + (i * 38)) - 100;
      Alarm_1_TT[i] =            Konnekting.getUINT8Param(PARAM_CH1_Alarm1toL     + (i * 38)) - 100;
      Sensor_Alarm1[i] =         Konnekting.getUINT16Param(PARAM_CH1_Alarm1sensor  + (i * 38));

      Alarm_2_HT[i] =            Konnekting.getUINT8Param(PARAM_CH1_Alarm2toH     + (i * 38)) - 100;
      Alarm_2_TT[i] =            Konnekting.getUINT8Param(PARAM_CH1_Alarm2toL     + (i * 38)) - 100;
      Sensor_Alarm2[i] =         Konnekting.getUINT16Param(PARAM_CH1_Alarm2sensor  + (i * 38));
    }


    //Multisnesoren
    static uint8_t Interval_sent_Multi          = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitZyklischesSendenMultiSensor));   // interval send Temp values
    static uint8_t Interval_sent_aenderung_Multi = ((uint8_t) Konnekting.getUINT8Param(PARAM_ZeitZyklischesSendenMultiSensor));   // interval send Temp values bei Wertänderung


    /******************* read DS18B20 Address from Konnekting Suite ***************************/
    /* Section 1-14 */
    for (int i = 0; i < COUNT_DS18B20_S1 ; i++) {
      Konnekting.getParamValue(PARAM_SensorID1 + (i * 2), DS18B20_address_S1[i]);
      if (DS18B20_address_S1[i][0] == 0x28) {
        tempSensorActive_S1[i] = true;
      }
      diff_T_S1[i] = Konnekting.getUINT8Param(PARAM_TempSendJump_ID1 + (i * 2));
    }
    /* Section 15-28 */
    for (int i = 0; i < COUNT_DS18B20_S2 ; i++) {
      Konnekting.getParamValue(PARAM_SensorID15 + (i * 2), DS18B20_address_S2[i]);
      if (DS18B20_address_S2[i][0] == 0x28) {
        tempSensorActive_S2[i] = true;
      }
      diff_T_S2[i] = Konnekting.getUINT8Param(PARAM_TempSendJump_ID15 + (i * 2));
    }
    /* Section 29-42 */
    for (int i = 0; i < COUNT_DS18B20_S3 ; i++) {
      Konnekting.getParamValue(PARAM_SensorID29 + (i * 2), DS18B20_address_S3[i]);
      if (DS18B20_address_S3[i][0] == 0x28) {
        tempSensorActive_S3[i] = true;
      }
      diff_T_S3[i] = Konnekting.getUINT8Param(PARAM_TempSendJump_ID29 + (i * 2));
    }



    /******************* read Multisensor Address from Konnekting Suite ***************************/

    // Für Multisensoren 1-5 ohne NTC
    for (int i = 0; i < MAX_multisenor_o_NTC ; i++) {
      Konnekting.getParamValue(i * 7 + PARAM_MS1_2438id, ms_DS2438_address[i]);
      if (ms_DS2438_address[i][0] == 0x26) {
        ms_DS2438_1_Active[i] = true;
      }
      Konnekting.getParamValue(i * 7 + PARAM_MS1_2438id2, ms_DS2438_2_address[i]);
      if (ms_DS2438_2_address[i][0] == 0x26) {
        ms_DS2438_2_Active[i] = true;
      }
      oneWire_MS_CH[i] =  Konnekting.getUINT8Param(i * 7 + PARAM_MS1_BUS);
      ms_Device[i]     =  Konnekting.getUINT8Param(i * 7 + PARAM_MS1_Device);
      ms_diff_H[i]     =  Konnekting.getUINT8Param(i * 7 + PARAM_MS1_Hsprung);
      ms_diff_L[i]     =  Konnekting.getUINT8Param(i * 7 + PARAM_MS1_LUXsprung);
      ms_diff_V[i]     = (Konnekting.getUINT8Param(i * 7 + PARAM_MS1_VOCsprung) * 2);
    }


    // Für Multisensoren 6-10 mit NTC
    for (int i = 0; i < MAX_multisenor_m_NTC ; i++) {
      Konnekting.getParamValue(i * 9 + PARAM_MS6_2438id, ms_DS2438_address[i + MAX_multisenor_o_NTC]);
      if (ms_DS2438_address[i + MAX_multisenor_o_NTC][0] == 0x26) {
        ms_DS2438_1_Active[i + MAX_multisenor_o_NTC] = true;
      }
      Konnekting.getParamValue(i * 9 + PARAM_MS6_2438id2, ms_DS2438_2_address[i + MAX_multisenor_o_NTC]);
      if (ms_DS2438_2_address[i + MAX_multisenor_o_NTC][0] == 0x26) {
        ms_DS2438_2_Active[i + MAX_multisenor_o_NTC] = true;
      }
      oneWire_MS_CH[i + MAX_multisenor_o_NTC] =  Konnekting.getUINT8Param(i * 9 + PARAM_MS6_BUS);
      ms_Device[i + MAX_multisenor_o_NTC]     =  Konnekting.getUINT8Param(i * 9 + PARAM_MS6_Device);
      ms_diff_H[i + MAX_multisenor_o_NTC]     =  Konnekting.getUINT8Param(i * 9 + PARAM_MS6_Hsprung);
      ms_diff_L[i + MAX_multisenor_o_NTC]     =  Konnekting.getUINT8Param(i * 9 + PARAM_MS6_LUXsprung);
      ms_diff_V[i + MAX_multisenor_o_NTC]     = (Konnekting.getUINT8Param(i * 9 + PARAM_MS6_VOCsprung) * 2);
      NTC_R1   [i + MAX_multisenor_o_NTC]     =  Konnekting.getUINT16Param(i * 9 + PARAM_MS6_TempR1);
      NTC_bWert[i + MAX_multisenor_o_NTC]     =  Konnekting.getUINT16Param(i * 9 + PARAM_MS6_bWert);
    }




    /******************* read iButton Address from Konnekting Suite ***************************/
    Konnekting.getParamValue(PARAM_iB1id, iButton0);
    Konnekting.getParamValue(PARAM_iB2id, iButton1);
    Konnekting.getParamValue(PARAM_iB3id, iButton2);
    Konnekting.getParamValue(PARAM_iB4id, iButton3);
    Konnekting.getParamValue(PARAM_iB5id, iButton4);
    Konnekting.getParamValue(PARAM_iB6id, iButton5);
    Konnekting.getParamValue(PARAM_iB7id, iButton6);
    Konnekting.getParamValue(PARAM_iB8id, iButton7);
    Konnekting.getParamValue(PARAM_iB9id, iButton8);
    Konnekting.getParamValue(PARAM_iB10id, iButton9);




    //iButtons Parameter
    readiButton_bus =  (uint8_t)  Konnekting.getUINT8Param(PARAM_iButton_BUS);
    sendZyklStatus  =  (uint8_t)  Konnekting.getUINT8Param(PARAM_statuszyklischsendenibutton);
    allAnwSend      =  (uint8_t)  Konnekting.getUINT8Param(PARAM_allAnwesend);
    allAbw_B_S      =  (uint8_t)  Konnekting.getUINT8Param(PARAM_allAbw_B_S);             // 0 = OFF | 1 = bool | 2 = Szene
    szenenWahl      =  (uint8_t)  Konnekting.getUINT8Param(PARAM_wahlSzene);
    delayALLAbw     =  (uint8_t)  Konnekting.getUINT8Param(PARAM_delayAllAbw);
    static uint8_t mem  = (uint8_t) Konnekting.getUINT8Param(PARAM_infoWrongID);
    if (mem == 1 || mem == 3)
      infoWrongID     =  true;
    if (mem == 2 || mem == 3)
      sendinfoWrongID =  true;
    blockiButtons   =  (uint8_t)  Konnekting.getUINT8Param(PARAM_BlockTime);
    AbwGruppe1      =  (uint16_t)  Konnekting.getUINT16Param(PARAM_Group1);
    AbwGruppe2      =  (uint16_t)  Konnekting.getUINT16Param(PARAM_Group2);
    AbwGruppe3      =  (uint16_t)  Konnekting.getUINT16Param(PARAM_Group3);

    for (int i = 0; i < MAX_iButton; i++) {
      static uint8_t mem2;
      mem2  = (uint8_t) Konnekting.getUINT8Param(i * 3 + PARAM_iB1isActive);     //input active?
      Debug.println(F("Door: %d"), mem2);
      if (mem2 >= 1)
        iButtonActive[i] = true;
      if (mem2 == 2)
        iButtonDoorReq[i] = true;
      iButtonInvOutput[i] = (bool)Konnekting.getUINT8Param(i * 3 + PARAM_iB1invOutput);  //invert binary output: 0=normal|1=inverted
    }



    /****************** Set Timer values **************************************************/
    //interval send new Sensor ID KNx
    switch (Interval_sent_new_ID) {
      case 0: sendNewID = false;                             break;   //OFF
      case 1: sent_ID_counter = 5000;   sendNewID = true;    break;   //5sec
      case 2: sent_ID_counter = 10000;  sendNewID = true;    break;   //10sec
      case 3: sent_ID_counter = 30000;  sendNewID = true;    break;   //30sec
      case 4: sent_ID_counter = 60000;  sendNewID = true;    break;   //1min
      case 5: sent_ID_counter = 300000; sendNewID = true;    break;   //5min
      default:
#ifdef KDEBUG
        Debug.println("Send New ID Temp ist irgendwas\n");
#endif
        break;
    }

    //interval send Temp values KNX CH1
    switch (Interval_sent_TvalueCH1) {
      case 0: sendKNXtempCH1 = false;        break;    //off
      case 1: sent_temp_counterCH1 = 60000;  break;    //1min
      case 2: sent_temp_counterCH1 = 120000; break;    //2min
      case 3: sent_temp_counterCH1 = 180000; break;    //3min
      case 4: sent_temp_counterCH1 = 300000; break;    //5min
      case 5: sent_temp_counterCH1 = 600000; break;    //10min
      case 6: sent_temp_counterCH1 = 1800000; break;   //30min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX Temp CH1 ist irgendwas\n");
#endif
        break;
    }
    //interval send Temp values KNX CH2
    switch (Interval_sent_TvalueCH2) {
      case 0: sendKNXtempCH2 = false;        break;          //off
      case 1: sent_temp_counterCH2 = 60000 + 700; break;    //1min  +700 damit es im Vergleich zu den anderen CH nicht zu überschneidungen kommt
      case 2: sent_temp_counterCH2 = 120000 + 700; break;   //2min
      case 3: sent_temp_counterCH2 = 180000 + 700; break;   //3min
      case 4: sent_temp_counterCH2 = 300000 + 700; break;   //5min
      case 5: sent_temp_counterCH2 = 600000 + 700; break;   //10min
      case 6: sent_temp_counterCH2 = 1800000 + 700; break;  //30min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX Temp CH2 ist irgendwas\n");
#endif
        break;
    }
    //interval send Temp values KNX CH3
    switch (Interval_sent_TvalueCH3) {
      case 0: sendKNXtempCH3 = false;              break;    //off
      case 1: sent_temp_counterCH3 = 60000 - 550;   break;   //1min  -550 damit es im Vergleich zu den anderen CH nicht zu überschneidungen kommt
      case 2: sent_temp_counterCH3 = 120000 - 550;  break;   //2min
      case 3: sent_temp_counterCH3 = 180000 - 550;  break;   //3min
      case 4: sent_temp_counterCH3 = 300000 - 550;  break;   //5min
      case 5: sent_temp_counterCH3 = 600000 - 550;  break;   //10min
      case 6: sent_temp_counterCH3 = 1800000 - 550;  break;  //30min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX Temp CH3 ist irgendwas\n");
#endif
        break;
    }

    //interval send Temp values KNX CH1
    switch (Interval_sent_aenderung_TvalueCH1) {
      case 0: sendKNXtemp_aenderung_CH1 = false;        break;     //off
      case 1: sent_temp_aenderung_counterCH1 = 300000;  break;    //5min
      case 2: sent_temp_aenderung_counterCH1 = 600000; break;     //10min
      case 3: sent_temp_aenderung_counterCH1 = 900000; break;     //15min
      case 4: sent_temp_aenderung_counterCH1 = 1800000; break;    //30min
      case 5: sent_temp_aenderung_counterCH1 = 3600000; break;    //60min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX Temp aenderung CH1 ist irgendwas\n");
#endif
        break;
    }

    //interval send Temp values KNX CH2
    switch (Interval_sent_aenderung_TvalueCH2) {
      case 0: sendKNXtemp_aenderung_CH2 = false;        break;    //off
      case 1: sent_temp_aenderung_counterCH2 = 300000;  break;    //5min
      case 2: sent_temp_aenderung_counterCH2 = 600000; break;     //10min
      case 3: sent_temp_aenderung_counterCH2 = 900000; break;     //15min
      case 4: sent_temp_aenderung_counterCH2 = 1800000; break;    //30min
      case 5: sent_temp_aenderung_counterCH2 = 3600000; break;    //60min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX Temp Änderung CH2 ist irgendwas\n");
#endif
        break;
    }
    //interval send Temp values KNX CH3
    switch (Interval_sent_aenderung_TvalueCH3) {
      case 0: sendKNXtemp_aenderung_CH3 = false;        break;    //off
      case 1: sent_temp_aenderung_counterCH3 = 300000;  break;    //5min
      case 2: sent_temp_aenderung_counterCH3 = 600000; break;     //10min
      case 3: sent_temp_aenderung_counterCH3 = 900000; break;     //15min
      case 4: sent_temp_aenderung_counterCH3 = 1800000; break;    //30min
      case 5: sent_temp_aenderung_counterCH3 = 3600000; break;    //60min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX Temp Änderung CH3 ist irgendwas\n");
#endif
        break;
    }

    //perodically sent Ibutton status KNX
    switch (sendZyklStatus) {
      case 0: sendKNXiButtons = false;
      case 1: freq_sent_counter = 10000;  break;    //10sec
      case 2: freq_sent_counter = 30000;  break;    //30sec
      case 3: freq_sent_counter = 60000;  break;    //1min
      case 4: freq_sent_counter = 120000; break;    //2min
      case 4: freq_sent_counter = 180000; break;    //3min
      case 5: freq_sent_counter = 300000; break;    //5min
      case 7: freq_sent_counter = 600000; break;    //10min
      case 8: freq_sent_counter = 900000; break;    //15min
      case 9: freq_sent_counter = 1800000; break;   //30min
      case 10: freq_sent_counter = 3600000; break;   //60min
      default:
#ifdef KDEBUG
        Debug.println("Send iButton Temp ist irgendwas\n");
#endif
        break;
    }

    //Allabwesend delay
    switch (delayALLAbw) {
      case 0: iButton_allAbw_delay = false;
      case 1: delay_counter = 10000;  break;    //10sec
      case 2: delay_counter = 30000;  break;    //30sec
      case 3: delay_counter = 60000;  break;    //1min
      case 4: delay_counter = 120000; break;    //2min
      case 5: delay_counter = 180000; break;    //3min
      case 6: delay_counter = 300000; break;    //5min
      case 7: delay_counter = 600000; break;    //10min
      case 8: delay_counter = 900000; break;    //15min
      case 9: delay_counter = 1800000; break;   //30min
      case 10: delay_counter = 3600000; break;   //60min
      default:
#ifdef KDEBUG
        Debug.println("Delay all Abwesend ist irgendwas\n");
#endif
        break;
    }


    //interval send Multisensor values KNX
    switch (Interval_sent_Multi) {
      case 0: sendKNXmultisensor = false;  break;    //OFF
      case 1: sent_multi_counter = 30000;  break;    //30sec
      case 2: sent_multi_counter = 60000;  break;    //1min
      case 3: sent_multi_counter = 120000; break;    //2min
      case 4: sent_multi_counter = 180000; break;    //3min
      case 5: sent_multi_counter = 300000; break;    //5min
      case 6: sent_multi_counter = 600000; break;    //10min
      case 7: sent_multi_counter = 1800000; break;   //30min
      case 8: sent_multi_counter = 3600000; break;   //60minv
      default:
#ifdef KDEBUG
        Debug.println("Send Multisnesor ist irgendwas\n");
#endif
        break;
    }

    //interval send Multisnesor values Wertänderung
    switch (Interval_sent_aenderung_Multi) {
      case 0: sendKNXMS_aenderung = false;         break;    //off
      case 1: sent_MS_aenderung_counter = 300000;  break;    //5min
      case 2: sent_MS_aenderung_counter = 600000;  break;     //10min
      case 3: sent_MS_aenderung_counter = 900000;  break;     //15min
      case 4: sent_MS_aenderung_counter = 1800000; break;    //30min
      case 5: sent_MS_aenderung_counter = 3600000; break;    //60min
      default:
#ifdef KDEBUG
        Debug.println("Send KNX MS Änderung ist irgendwas\n");
#endif
        break;
    }

    //Options="00=OFF|01=1min|02=5min|03=10min|04=15min|05=20min|06=30min|07=60min"
    //interval send ALIVE MSG
    switch (alive_msg_time) {
      case 0: alive_msg_ON = false;         break;    //off
      case 1: sent_alive_counter = 60000;   break;    //1min
      case 2: sent_alive_counter = 300000;  break;    //5min
      case 3: sent_alive_counter = 600000;  break;    //10min
      case 4: sent_alive_counter = 900000;  break;    //15min
      case 5: sent_alive_counter = 1200000; break;    //20min
      case 6: sent_alive_counter = 1800000; break;    //30min
      case 7: sent_alive_counter = 3600000; break;    //60min
      default:
#ifdef KDEBUG
        Debug.println("Send Alive MSG ist irgendwas\n");
#endif
        break;
    }





    /******************* Set Strong Pullup  ***************************************************/
    if (CH1_active) {
      if (oneW_CH1_StrongPU_ON)
        oneWire_CH1.setStrongPullup();
    }
    if (CH2_active) {
      if (oneW_CH2_StrongPU_ON)
        oneWire_CH2.setStrongPullup();
    }
    if (CH3_active) {
      if (oneW_CH3_StrongPU_ON)
        oneWire_CH3.setStrongPullup();
    }



    /*****************************************************************************************/
    /******************* I2C DS18B20 Init ****************************************************/
    /*****************************************************************************************/
    /*    SET ALARM FUNKTION        */
    static bool isalarm1;
    static bool isalarm2;
    /***  Section 1-10 CH1 ***/
    for (int i = 0; i < COUNT_DS18B20_S1; i++) {
      //check ob Alarm1 für diesen Sensor aktiv ist
      if (bitRead(Sensor_Alarm1[0], i))
        isalarm1 = true;
      else
        isalarm1 = false;
      if (bitRead(Sensor_Alarm2[0], i))
        isalarm2 = true;
      else
        isalarm2 = false;

      DS18B20_S1[i].init(&oneWire_CH1, DS18B20_address_S1[i], tempSensorActive_S1[i], diff_T_S1[i], isalarm1, Alarm_1_HT[0], Alarm_1_TT[0], isalarm2, Alarm_2_HT[0], Alarm_2_TT[0] );
      DS18B20[i].init(&oneWire_CH1, DS18B20_address_S1[i], tempSensorActive_S1[i], diff_T_S1[i], isalarm1, Alarm_1_HT[0], Alarm_1_TT[0], isalarm2, Alarm_2_HT[0], Alarm_2_TT[0] );
    }
    /***  Section 11-20 CH2 ***/
    for (int i = 0; i < COUNT_DS18B20_S2; i++) {
      //check ob Alarm1 für diesen Sensor aktiv ist
      if (bitRead(Sensor_Alarm1[1], i))
        isalarm1 = true;
      else
        isalarm1 = false;
      if (bitRead(Sensor_Alarm2[1], i))
        isalarm2 = true;
      else
        isalarm2 = false;

      DS18B20_S2[i].init(&oneWire_CH2, DS18B20_address_S2[i], tempSensorActive_S2[i], diff_T_S2[i], isalarm1, Alarm_1_HT[1], Alarm_1_TT[1], isalarm2, Alarm_2_HT[1], Alarm_2_TT[1]);
      DS18B20[i + COUNT_DS18B20_S1].init(&oneWire_CH2, DS18B20_address_S2[i], tempSensorActive_S2[i], diff_T_S2[i], isalarm1, Alarm_1_HT[1], Alarm_1_TT[1], isalarm2, Alarm_2_HT[1], Alarm_2_TT[1]);
    }
    /***  Section 21-30 CH3 ***/
    if (CH3_active) {
      for (int i = 0; i < COUNT_DS18B20_S3; i++) {
        //check ob Alarm1 für diesen Sensor aktiv ist
        if (bitRead(Sensor_Alarm1[2], i))
          isalarm1 = true;
        else
          isalarm1 = false;
        if (bitRead(Sensor_Alarm2[2], i))
          isalarm2 = true;
        else
          isalarm2 = false;

        DS18B20_S3[i].init(&oneWire_CH3, DS18B20_address_S3[i], tempSensorActive_S3[i], diff_T_S3[i], isalarm1, Alarm_1_HT[2], Alarm_1_TT[2], isalarm2, Alarm_2_HT[2], Alarm_2_TT[2]);
        DS18B20[i + COUNT_DS18B20_S1 + COUNT_DS18B20_S2].init(&oneWire_CH3, DS18B20_address_S3[i], tempSensorActive_S3[i], diff_T_S3[i], isalarm1, Alarm_1_HT[2], Alarm_1_TT[2], isalarm2, Alarm_2_HT[2], Alarm_2_TT[2]);
      }
    }

    /******************************************************************************************/
    /******************* Multisensors Init ****************************************************/
    /******************************************************************************************/
    for (int i = 0; i < MAX_multisenor ; i++) {
      /* CH1 */
      if (CH1_active && oneWire_MS_CH[i] == 1) {
        multiSensor[i].init(&oneWire_CH1, ms_DS2438_address[i], ms_DS2438_2_address[i], ms_Device[i], ms_DS2438_1_Active[i], ms_DS2438_2_Active[i], ms_diff_H[i], ms_diff_L[i], ms_diff_V[i]);
      }
      /* CH2 */
      if (CH2_active && oneWire_MS_CH[i] == 2) {
        multiSensor[i].init(&oneWire_CH2, ms_DS2438_address[i], ms_DS2438_2_address[i], ms_Device[i], ms_DS2438_1_Active[i], ms_DS2438_2_Active[i], ms_diff_H[i], ms_diff_L[i], ms_diff_V[i]);
      }
      /* CH3 */
      if (CH3_active && oneWire_MS_CH[i] == 3) {
        multiSensor[i].init(&oneWire_CH3, ms_DS2438_address[i], ms_DS2438_2_address[i], ms_Device[i], ms_DS2438_1_Active[i], ms_DS2438_2_Active[i], ms_diff_H[i], ms_diff_L[i], ms_diff_V[i]);
      }
    }



    /******************************************************************************************/
    /******************* 1-Wire CH1 ***********************************************************/
    /******************************************************************************************/

    if (oneWire_CH1.readStatusShortDet()) {
#ifdef KDEBUG
      Debug.println(F("CH1: 1-W Short"));
#endif
      oneWire_CH1.reset();
      CH1_short = true;
    }
    else
    {
      CH1_short = false;
      /******************* I2C DS18B20 Setup up Section 1 - 14 **********************************/
      /* Section CH1 */
      if (CH1_active) {
        for (int i = 0; i < COUNT_DS18B20_S1; i++) {
          if (DS18B20_S1[i].isConnected()) {
            tempSensorError_S1[i] = false;
            DS18B20_S1[i].setResolution(resolution[TempResolution_CH1]);
          }
          else {
            if (tempSensorActive_S1[i] == true) {
              tempSensorError_S1[i] = true;
            }
          }
        }

        /******************* Multisensor Setup up CH1 *********************************************/
        for (int i = 0; i < MAX_multisenor ; i++) {
          if (CH1_active && oneWire_MS_CH[i] == 1) {
            if (multiSensor[i].DS2438_1_isConnected()) {
              ms_DS2438_1_tempSensorError[i] = false;
            }
            else {
              if (ms_DS2438_1_Active[i] == true) {
                ms_DS2438_1_tempSensorError[i] = true;
              }
            }
            if (multiSensor[i].DS2438_2_isConnected()) {
              ms_DS2438_2_tempSensorError[i] = false;
            }
            else {
              if (ms_DS2438_2_Active[i] == true) {
                ms_DS2438_2_tempSensorError[i ] = true;
              }
            }
          }
        }
        /************************** Ibutton LED SW *************************************************/
        if (readiButton_bus == 1) {
          DS2408_SW.init(&oneWire_CH1, DS2408_address);
          DS2408_SW_2.init(&oneWire_CH1, DS2408_address_2);
          DS2408_found = DS2408_SW.find();
          DS2408_found_2 = DS2408_SW_2.find();
        }
      }
    }

    /******************************************************************************************/
    /******************* 1-Wire CH2 ***********************************************************/
    /******************************************************************************************/
    if (oneWire_CH2.readStatusShortDet()) {
#ifdef KDEBUG
      Debug.println(F("CH2: 1-W Short"));
#endif
      oneWire_CH2.reset();
      CH2_short = true;
    }
    else
    {
      CH2_short = false;
      /******************* I2C DS18B20 Setup up  15 - 28 **************************************/
      /* Section CH2 */
      if (CH2_active) {
        for (int i = 0; i < COUNT_DS18B20_S2; i++) {
          if (DS18B20_S2[i].isConnected()) {
            tempSensorError_S2[i] = false;
            DS18B20_S2[i].setResolution(resolution[TempResolution_CH2]);
          }
          else {
            if (tempSensorActive_S2[i] == true) {
              tempSensorError_S2[i] = true;
            }
          }


          /******************* Miltisensor Setup up CH2 *********************************************/
          for (int i = 0; i < MAX_multisenor ; i++) {
            if (CH2_active && oneWire_MS_CH[i] == 2) {
              if (multiSensor[i].DS2438_1_isConnected()) {
                ms_DS2438_1_tempSensorError[i] = false;
              }
              else {
                if (ms_DS2438_1_Active[i] == true) {
                  ms_DS2438_1_tempSensorError[i ] = true;
                }
              }
              if (multiSensor[i].DS2438_2_isConnected()) {
                ms_DS2438_2_tempSensorError[i] = false;
              }
              else {
                if (ms_DS2438_2_Active[i] == true) {
                  ms_DS2438_2_tempSensorError[i ] = true;
                }
              }
            }
          }
        }
        /************************** Ibutton LED SW *************************************************/
        if (readiButton_bus == 2) {
          DS2408_SW.init(&oneWire_CH2, DS2408_address);
          DS2408_SW_2.init(&oneWire_CH2, DS2408_address_2);
          DS2408_found = DS2408_SW.find();
          DS2408_found_2 = DS2408_SW_2.find();
          DS2408_SW.set_LED_DS2408(0, false);
          DS2408_SW.set_LED_DS2408(1, false);
          DS2408_SW.set_LED_DS2408(4, false);
          DS2408_SW.set_LED_DS2408(5, false);
        }
      }
    }


    /******************************************************************************************/
    /******************* 1-Wire CH3 ***********************************************************/
    /******************************************************************************************/
    if (oneWire_CH3.readStatusShortDet()) {
#ifdef KDEBUG
      Debug.println(F("CH3: 1-W Short"));
#endif
      oneWire_CH3.reset();
      CH3_short = true;
    }
    else
    {
      CH3_short = false;
      /******************* I2C DS18B20 Setup up  29 - 42 **************************************/
      /* Section CH3 */
      if (CH3_active) {
        for (int i = 0; i < COUNT_DS18B20_S3; i++) {
          if (DS18B20_S3[i].isConnected()) {
            tempSensorError_S3[i] = false;
            tempSensorError_S3[i] = false;
            DS18B20_S3[i].setResolution(resolution[TempResolution_CH3]);
          }
          else {
            if (tempSensorActive_S3[i] == true) {
              tempSensorError_S3[i] = true;
            }
          }
        }

        /******************* Miltisensor Setup up CH3 *********************************************/
        for (int i = 0; i < MAX_multisenor ; i++) {
          if (CH3_active && oneWire_MS_CH[i] == 3) {
            if (multiSensor[i].DS2438_1_isConnected()) {
              ms_DS2438_1_tempSensorError[i] = false;
            }
            else {
              if (ms_DS2438_1_Active[i] == true) {
                ms_DS2438_1_tempSensorError[i ] = true;
              }
            }
            if (multiSensor[i].DS2438_2_isConnected()) {
              ms_DS2438_2_tempSensorError[i] = false;
            }
            else {
              if (ms_DS2438_2_Active[i] == true) {
                ms_DS2438_2_tempSensorError[i ] = true;
              }
            }
          }
        }
        /************************** Ibutton LED SW *************************************************/
        if (readiButton_bus == 3) {
          DS2408_SW.init(&oneWire_CH3, DS2408_address);
          DS2408_SW_2.init(&oneWire_CH3, DS2408_address_2);
          DS2408_found = DS2408_SW.find();
          DS2408_found_2 = DS2408_SW_2.find();
        }
      }
    }







    /******************************************************************************************/
    /******************* USB Debug Outputs*****************************************************/
    /******************************************************************************************/
#ifdef KDEBUG
    delay(500);
    Debug.println(" ");
    Debug.println(" ");
    Debug.println("******************************************************");
    Debug.println("   1-Wire Settings");
    Debug.println("******************************************************");
    if (CH1_active) {
      Debug.println(F("1-Wire CH1: AKTIV   ->  Strong PullUp: %d"), oneW_CH1_StrongPU_ON);
    }
    else {
      Debug.println("1-Wire CH1: INAKTIV");
    }
    if (CH2_active) {
      Debug.println(F("1-Wire CH2: AKTIV   ->  Strong PullUp: %d"), oneW_CH2_StrongPU_ON);
    }
    else {
      Debug.println("1-Wire CH2: INAKTIV");
    }
    if (CH3_active) {
      Debug.println(F("1-Wire CH3: AKTIV   ->  Strong PullUp: %d"), oneW_CH3_StrongPU_ON);
    }
    else {
      Debug.println("1-Wire CH3: INAKTIV");
    }
    Debug.println(F(" "));
    Debug.println(F(" "));
    if ((readNewID_bus == 1 && CH1_active) || (readNewID_bus == 2 && CH2_active) || (readNewID_bus == 3 && CH3_active) ) {
      Debug.println("******************************************************");
      Debug.println("  New ID ");
      Debug.println("******************************************************");
      Debug.println(F("1-Wire CH: %d"), readNewID_bus);
      Debug.println(F(" "));
      if (sendNewID) {
        Debug.println("send new ID = true");
      }
      else {
        Debug.println("send new ID = fasle");
      }
      Debug.println("interval send ID: %i", sent_ID_counter);
      Debug.println(F(" "));
      Debug.println(F(" "));
    }
    Debug.println("******************************************************");
    Debug.println("  Alive MSG ");
    Debug.println("******************************************************");
    if (alive_msg_ON) {
      Debug.println(F("Live MSG: %dms"), sent_alive_counter);
    }
    else
      Debug.println(F("Live MSG: OFF"));
    Debug.println(F(" "));
    Debug.println(F(" "));
    Debug.println("******************************************************");
    Debug.println("  Temp Sensors ");
    Debug.println("******************************************************");
    if (CH1_active) {
      Debug.println("interval send Temp CH1 values: %i", sent_temp_counterCH1);
      if (sendKNXtemp_aenderung_CH1)
        Debug.println("send Änderung Temp CH1 values: %i", sent_temp_aenderung_counterCH1);
      else
        Debug.println(F("send Änderung Temp CH1 values: OFF"));
    }
    if (CH2_active) {
      Debug.println(F(" "));
      Debug.println("interval send Temp CH2 values: %i", sent_temp_counterCH2);
      if (sendKNXtemp_aenderung_CH2)
        Debug.println("send Änderung Temp CH2 values: %i", sent_temp_aenderung_counterCH2);
      else
        Debug.println(F("send Änderung Temp CH2 values: OFF"));
    }
    if (CH3_active) {
      Debug.println(F(" "));
      Debug.println("interval send Temp CH3 values: %i", sent_temp_counterCH3);
      if (sendKNXtemp_aenderung_CH3)
        Debug.println("send Änderung Temp CH3 values: %i", sent_temp_aenderung_counterCH3);
      else
        Debug.println(F("send Änderung Temp CH3 values: OFF"));
    }
    Debug.println(F(" "));
    /*Section 1*/
    if (CH1_active) {
      Debug.println(F("Section1: CH1  "));
      for (int i = 0; i < COUNT_DS18B20_S1; i++) {
        Debug.print(F("  Temp-Sensor_%d:  "), i + 1);
        print_DS18B20_Addr(DS18B20_address_S1[i]);
        Debug.print(F("| Res: %dBIT  "), DS18B20[i].getResolution());
        if (DS18B20_S1[i].getisActive() == true) {
          Debug.print(F("Active   "));
          if (tempSensorError_S1[i] == false) {
            Debug.print(F("| Connected "));
            if (DS18B20_S1[i].isSend_Temp())
              Debug.println(F(" |  senden:   +/-%0.1f°C "), diff_T_S1[i] / 10.0);
            else
              Debug.println(F(" |  senden:   zyklisch "));
          }
          else {
            Debug.println(F("| ERROR"));
          }
        }
        else {
          Debug.println(F("Inactive"));
        }
        Debug.println(F("Alarm1: %d"), DS18B20_S1[i].getAlarm1());
        Debug.println(F("Alarm2: %d"), DS18B20_S1[i].getAlarm2());
      }
      Debug.println(F("Alarm1: "));
      Debug.println(F("Sensoren: %d"), Sensor_Alarm1[0]);
      Debug.println(F("HT: %0.1f°C"), Alarm_1_HT[0]);
      Debug.println(F("TT: %0.1f°C"), Alarm_1_TT[0]);
      Debug.println(F("Alarm2: "));
      Debug.println(F("Sensoren: %d"), Sensor_Alarm2[0]);
      Debug.println(F("HT: %0.1f°C"), Alarm_2_HT[0]);
      Debug.println(F("TT: %0.1f°C"), Alarm_2_TT[0]);
    }

    Debug.println(" ");
    /*Section 2*/
    if (CH2_active) {
      Debug.println(F("Section2: CH2  "));
      for (int i = 0; i < COUNT_DS18B20_S2; i++) {
        Debug.print(F("  Temp-Sensor_%d:  "), i + COUNT_DS18B20_S1 + 1);
        print_DS18B20_Addr(DS18B20_address_S2[i]);
        Debug.print(F("Res: %dBIT  "), DS18B20_S2[i].getResolution());
        if (DS18B20_S2[i].getisActive() == true) {
          Debug.print("Active   ");
          if (tempSensorError_S2[i] == false) {
            Debug.print(F("| Connected "));
            if (DS18B20_S2[i].isSend_Temp())
              Debug.println(F(" |  senden:   +/-%0.1f°C "), diff_T_S2[i] / 10.0);
            else
              Debug.println(F(" |  senden:   zyklisch "));
          }
          else {
            Debug.println(F("| ERROR"));
          }
        }
        else {
          Debug.println("Inactive ");
        }
        Debug.println(F("Alarm1: %d"), DS18B20_S2[i].getAlarm1());
        Debug.println(F("Alarm2: %d"), DS18B20_S2[i].getAlarm2());
      }
    }
    /*Section 3*/
    if (CH3_active) {
      Debug.println(F("Section3: CH3"));
      for (int i = 0; i < COUNT_DS18B20_S3; i++) {
        Debug.print(F("  Temp-Sensor_%d:  "), i + COUNT_DS18B20_S1 + COUNT_DS18B20_S2 + 1);
        print_DS18B20_Addr(DS18B20_address_S3[i]);
        Debug.print(F("Res: %dBIT  "), DS18B20_S3[i].getResolution());
        if (DS18B20_S3[i].getisActive() == true) {
          Debug.print("Active   ");
          if (tempSensorError_S3[i] == false) {
            Debug.print(F("| Connected "));
            if (DS18B20_S3[i].isSend_Temp())
              Debug.println(F(" |  senden:   +/-%0.1f°C "), diff_T_S3[i] / 10.0);
            else
              Debug.println(F(" |  senden:   zyklisch "));
          }
          else {
            Debug.println(F("| ERROR"));
          }
        } // isActiv
        else {
          Debug.println("Inactive ");
        }
        Debug.println(F("Alarm1: %d"), DS18B20_S3[i].getAlarm1());
        Debug.println(F("Alarm2: %d"), DS18B20_S3[i].getAlarm2());
      } // for
    } // if CH3 active



    Debug.println(" ");
    Debug.println("******************************************************");
    Debug.println("   Multisenesor");
    Debug.println("******************************************************");
    Debug.println("*");
    for (int i = 0; i < MAX_multisenor ; i++) {
      if ((oneWire_MS_CH[i] == 1 && CH1_active) || (oneWire_MS_CH[i] == 2 && CH2_active) || (oneWire_MS_CH[i] == 3 && CH3_active) ) {
        Debug.println(F("Multisensor %d"), i + 1);
        Debug.println(F("  CH:%d"), oneWire_MS_CH[i]);
        Debug.print(F("  DS2438   "));
        print_Multisensor_Addr(ms_DS2438_address[i]);
        Debug.print(F(" |"));
        if (ms_DS2438_1_Active[i] == true) {
          Debug.print("  Active   ");
          if (ms_DS2438_1_tempSensorError[i] == false) {
            Debug.print(F("| Connected  |"));
          }
          else {
            Debug.print(F("| ERROR  |"));
          }
          Debug.print(F(" Sensor: "));
          print_Multisensor_Device1(ms_Device[i]);
        }
        else
          Debug.println("  Inactive |");
        Debug.print(F("  DS2438_2 "));
        print_Multisensor_Addr(ms_DS2438_2_address[i]);
        Debug.print(F(" |"));
        if (ms_DS2438_2_Active[i] == true) {
          Debug.print("  Active    |");
          if (ms_DS2438_2_tempSensorError[i] == false) {
            Debug.print(F("| Connected  |"));
          }
          else {
            Debug.print(F("| ERROR  |"));
          }
          Debug.print(F(" Sensor: "));
          print_Multisensor_Device2(ms_Device[i]);
        }
        else
          Debug.println("  Inactive |");

        Debug.println(F("  Hum : %d  | senden bei: +/-%d"), multiSensor[i].get_dev_hum(), ms_diff_H[i]);
        Debug.println(F("  VOC : %d  | senden bei: +/-%dppm"), multiSensor[i].get_dev_voc(), ms_diff_V[i]);
        Debug.println(F("  Lux : %d  | senden bei: +/-%dLUX"), multiSensor[i].get_dev_lux(), ms_diff_L[i]);
        Debug.println(F("  Lux2: %d"), multiSensor[i].get_dev_lux2());
        Debug.println(F("  NTC : %d | R1: %d | Bwert: %d"), multiSensor[i].get_dev_ntc(), NTC_R1[i], NTC_bWert[i] );
        Debug.println(F("  DS2438_T : %d"), multiSensor[i].get_dev_DS2438_Temp());
        Debug.println(" ");
      }
    }
    Debug.println("*");
    Debug.println("*");
    Debug.println("******************************************************");
    Debug.println("*");

    if (readiButton_bus > 0) { // 0 = OFF
      Debug.println(" ");
      Debug.println(" ");
      Debug.println("******************************************************");
      Debug.println("   iButtons");
      Debug.println("******************************************************");
      Debug.println("*");
      Debug.println(F("CH: %d"), readiButton_bus);
      Debug.println(F(" "));
      Debug.print("iButton1:  ");
      print_reg_iButton(iButton0);
      Debug.print("iButton2:  ");
      print_reg_iButton(iButton1);
      Debug.print("iButton3:  ");
      print_reg_iButton(iButton2);
      Debug.print("iButton4:  ");
      print_reg_iButton(iButton3);
      Debug.print("iButton5:  ");
      print_reg_iButton(iButton4);
      Debug.print("iButton6:  ");
      print_reg_iButton(iButton5);
      Debug.print("iButton7:  ");
      print_reg_iButton(iButton6);
      Debug.print("iButton8:  ");
      print_reg_iButton(iButton7);
      Debug.print("iButton9:  ");
      print_reg_iButton(iButton8);
      Debug.print("iButton10: ");
      print_reg_iButton(iButton9);
      Debug.println("*");
      Debug.println("******************************************************");
      Debug.println("*");
      Debug.println(F("Polling Zeit iButtons : %d ms"), poll_counter);
      Debug.println(" ");
      for (int m = 0; m < MAX_iButton; m++) {
        Debug.print(F("Button%d:  aktiv: "), m);
        Debug.print(F("%d |  inv: "), iButtonActive[m] );
        Debug.print(F("%d"), iButtonInvOutput[m] );
        Debug.println(F(" |  door: %d"), iButtonDoorReq[m] );
      }
      Debug.println(" ");
      if (allAnwSend)
        Debug.println(F("Alle Anwesend senden: aktiv") );
      else
        Debug.println(F("Alle Anwesend senden: inaktiv") );
      if (allAbw_B_S == 0)
        Debug.println(F("Alle Abwesend senden: inaktiv") );
      if  (allAbw_B_S == 1)
        Debug.println(F("Alle Abwesend senden: aktiv (bool)") );
      if  (allAbw_B_S == 2)
        Debug.println(F("Alle Abwesend senden: aktiv (Szene)") );
      Debug.println(F("Szene: %d"), szenenWahl);
      Debug.println(" ");
      if (!iButton_allAbw_delay)
        Debug.println(F("Delay bei alle Abwesend: OFF"));
      else
        Debug.println(F("Delay bei alle Abwesend: %d ms"), delay_counter);
      Debug.println(" ");
      if  (infoWrongID)
        Debug.println(F("Info unreg iButton ID: ON ") );
      else
        Debug.println(F("Info unreg iButton ID: OFF ") );
      if  (sendinfoWrongID)
        Debug.println(F("senden unreg iButton ID: ON ") );
      else
        Debug.println(F("senden unreg iButton ID: OFF ") );
      Debug.println(" ");
      Debug.println("*************************************");
      Debug.println("Init 1-Wire LED Switch");
      Debug.println(F("1-Wire Switch 1 found: %d"), DS2408_found);
      Debug.println(F("1-Wire Switch 2 found: %d"), DS2408_found_2);
      Debug.println("*************************************");
      Debug.println("*");
      Debug.println("******************************************************");
      Debug.println("*");
    }
#endif

  } // ENDE Factory Setting



  /******************* start Timer Search ID   *******************************/
  start_search_ID = millis();
  start_sent_Tvalue_Millis_CH1 = millis();
  start_sent_Tvalue_Millis_CH2 = millis();
  start_sent_Tvalue_Millis_CH3 = millis();
  start_sent_Multi_Millis = millis();

  // setzt Timer für zyklische Senden bei Wertänderung
  for (int i = 0 ; i < COUNT_DS18B20_S1 ; i++) {
    start_sent_aenderung_Tvalue_Millis_CH1[i] = millis();
  }
  for (int i = 0 ; i < COUNT_DS18B20_S2 ; i++) {
    start_sent_aenderung_Tvalue_Millis_CH2[i] = millis();
  }
  for (int i = 0 ; i < COUNT_DS18B20_S3 ; i++) {
    start_sent_aenderung_Tvalue_Millis_CH3[i] = millis();
  }
  for (int i = 0 ; i < MAX_iButton ; i++) {
    start_sent_aenderung_HUM_MS_Millis[i] = millis();
    start_sent_aenderung_LUX_MS_Millis[i] = millis();
    start_sent_aenderung_VOC_MS_Millis[i] = millis();
  }


  /******************* FINIDH SETUP  *****************************************/
#ifdef KDEBUG
  Debug.println("FINISH Setup");
#endif


  digitalWrite(LED_YELLOW, LOW);
}
