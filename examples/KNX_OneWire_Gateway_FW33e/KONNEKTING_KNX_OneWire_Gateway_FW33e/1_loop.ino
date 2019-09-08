// #################################################################################
// ### Loop()
// #################################################################################

void loop() {

  Knx.task();

  if (Konnekting.isReadyForApplication()) {

    /*
       State1: Aufgaben mit Prio:
          - iButtons
          - Anzeigen neue ID
       State2: Aufgaben mit weniger Prio:
          - DS18B20 Temperatursensoren
          - Multisensoren
          - KNX Nachrichten senden
    */

    switch (state_1)
    {
      case initState:
        sendKNX_1W_CH_state();
        state_1 = iButtonRead;
        break;

      case iButtonRead:
        if ((readiButton_bus == 1 && CH1_active) || (readiButton_bus == 2 && CH2_active) || (readiButton_bus == 3 && CH3_active) ) {
          //unsigned long ib_strat = millis();
          find_iButton();
          //Debug.println(F("stop: %dms"),ib_strat - millis());
          //Debug.println(F("read ibutton"));
        }
        state_1 = Group1;
        break;

      case read_NewID:
        if (searchNewID())
          state_1 = Group1;
        break;

      case Group1:
        switch (state_2)
        {
          case requestTemp:
            if (getTempvalue()) {
              readytoRead = true;
              finishRead = true;
              state_2 = readMultisensor_DS2438;
            }
            break;

          case readMultisensor_DS2438:
            if (Multisensor_DS2438()) {
              readytoRead = true;
              knx_send = true;                                          //Alle Sensoren eingelesen -> nun können zyklisch KNX Botschaften verschickt werden.
              state_2 = requestTemp;
            }
            break;

        }

        //einmaliges Senden bei Beginn
        if (finishRead == true && initalSend == true) {
#ifdef KDEBUG
          //  Debug.println(F("    ---------- init send KNX Temp -------"));
#endif
          KNX_Temp_Sensor_msg();
        }


        //Wartet bis alle Sensor-Werte eingelesen wurden bevor die erste KNX Botschaft verschickt wird
        if (knx_send) {

          //sendet Temp Werte KNX CH1
          current_sent_Tvalue_Millis_CH1 = millis();
          if (current_sent_Tvalue_Millis_CH1 - start_sent_Tvalue_Millis_CH1 >= sent_temp_counterCH1) {
#ifdef KDEBUG
            Debug.println(F("    ---------- send KNX Temp CH1 -------"));
#endif
            KNX_Temp_Sensor_msg_CH1();
            Knx.task();
          }

          //sendet Temp Werte KNX CH2
          current_sent_Tvalue_Millis_CH2 = millis();
          if (current_sent_Tvalue_Millis_CH2 - start_sent_Tvalue_Millis_CH2 >= sent_temp_counterCH2) {
#ifdef KDEBUG
            Debug.println(F("    ---------- send KNX Temp CH2 -------"));
#endif
            KNX_Temp_Sensor_msg_CH2();
            Knx.task();
          }

          //sendet Temp Werte KNX CH3
          current_sent_Tvalue_Millis_CH3 = millis();
          if (current_sent_Tvalue_Millis_CH3 - start_sent_Tvalue_Millis_CH3 >= sent_temp_counterCH3) {
#ifdef KDEBUG
            Debug.println(F("    ---------- send KNX Temp CH3 -------"));
#endif
            KNX_Temp_Sensor_msg_CH3();
            Knx.task();
          }


          //sendet Multisensor Werte KNX
          current_sent_Multi_Millis = millis();
          if (current_sent_Multi_Millis - start_sent_Multi_Millis >= sent_multi_counter && sendKNXmultisensor == true) {
#ifdef KDEBUG
            Debug.println(F("    ******** send KNX Multi ********"));
#endif
            KNX_Multi_Sensor_msg();
          }
        }


        // Prüft ob einlesen der Sensoren fertig ist. Wenn ja wird das einlesen der neuen ID gestartet
        if (readytoRead) {
          readytoRead = false;
          state_1 = read_NewID;
        }
        else {
          state_1 = iButtonRead;
        }


        // Sendet Nachricht wenn 1-Wire CH1 "short"
        if (CH1_short != CH1_short_old) {
#ifdef KDEBUG
          Debug.println(F("    ---------- send KNX 1-W CH1 ERROR %d -------"), CH1_short);
#endif
          Knx.write(COMOBJ_Status1WCh1, CH1_short);
          CH1_short_old = CH1_short;
        }

        // Sendet Nachricht wenn 1-Wire CH2 "short"
        if (CH2_short != CH2_short_old) {
#ifdef KDEBUG
          Debug.println(F("    ---------- send KNX 1-W CH2 ERROR %d -------"), CH2_short);
#endif
          Knx.write(COMOBJ_Status1WCh2, CH2_short);
          CH2_short_old = CH2_short;
        }

        // Sendet Nachricht wenn 1-Wire CH3 "short"
        if (CH3_short != CH3_short_old) {
#ifdef KDEBUG
          Debug.println(F("    ---------- send KNX 1-W CH3 ERROR %d -------"), CH3_short);
#endif
          Knx.write(COMOBJ_Status1WCh3, CH3_short);
          CH3_short_old = CH3_short;
        }



        // prüft ob bei zyklisches Senden bei Wertänderung notwending ist.
        if (sendKNXtemp_aenderung_CH1 && DS18B20_S1[step_count_aenderung].getisActive() && DS18B20_S1[step_count_aenderung].isSend_Temp()) {
          if (millis() - start_sent_aenderung_Tvalue_Millis_CH1[step_count_aenderung] >= sent_temp_aenderung_counterCH1) {
            sendKNX_Temp_CH1(step_count_aenderung);
            start_sent_aenderung_Tvalue_Millis_CH1[step_count_aenderung] = millis();
          }
        }
        if (sendKNXtemp_aenderung_CH2 && DS18B20_S2[step_count_aenderung].getisActive() && DS18B20_S2[step_count_aenderung].isSend_Temp()) {
          if (millis() - start_sent_aenderung_Tvalue_Millis_CH2[step_count_aenderung] >= sent_temp_aenderung_counterCH2) {
            sendKNX_Temp_CH2(step_count_aenderung);
            start_sent_aenderung_Tvalue_Millis_CH2[step_count_aenderung] = millis();
          }
        }
        if (sendKNXtemp_aenderung_CH3 && DS18B20_S3[step_count_aenderung].getisActive() && DS18B20_S3[step_count_aenderung].isSend_Temp()) {
          if (millis() - start_sent_aenderung_Tvalue_Millis_CH3[step_count_aenderung] >= sent_temp_aenderung_counterCH3) {
            sendKNX_Temp_CH3(step_count_aenderung);
            start_sent_aenderung_Tvalue_Millis_CH3[step_count_aenderung] = millis();
          }
        }
        step_count_aenderung++;
        if (step_count_aenderung >= COUNT_DS18B20_S1) {
          step_count_aenderung = 0;
        }

        //
        //    bool isSend_Hum();
        //    bool isSend_Lux();
        //    bool isSend_VOC();
        //unsigned long start_sent_aenderung_HUM_MS_Millis[MAX_iButton] = {0};
        //unsigned long start_sent_aenderung_LUX_MS_Millis[MAX_iButton] = {0};
        //unsigned long start_sent_aenderung_VOC_MS_Millis[MAX_iButton] = {0};


        // HUM
        if (sendKNXMS_aenderung && ms_DS2438_1_Active[ms_step_count_aenderung] && multiSensor[ms_step_count_aenderung].isSend_Hum()) {
          if (millis() -  start_sent_aenderung_HUM_MS_Millis[ms_step_count_aenderung] >= sent_MS_aenderung_counter ) {
            sendKNX_Multi_Hum(ms_step_count_aenderung);
            start_sent_aenderung_HUM_MS_Millis[ms_step_count_aenderung] = millis();
          }
        }
        // LUX
        if (sendKNXMS_aenderung && ms_DS2438_1_Active[ms_step_count_aenderung] && multiSensor[ms_step_count_aenderung].isSend_Lux()) {
          if (millis() -  start_sent_aenderung_LUX_MS_Millis[ms_step_count_aenderung] >= sent_MS_aenderung_counter ) {
            sendKNX_Multi_Lux(ms_step_count_aenderung);
            start_sent_aenderung_LUX_MS_Millis[ms_step_count_aenderung] = millis();
          }
        }
        // VOC
        if (sendKNXMS_aenderung && ms_DS2438_2_Active[ms_step_count_aenderung] && multiSensor[ms_step_count_aenderung].isSend_VOC()) {
          if (millis() -  start_sent_aenderung_VOC_MS_Millis[ms_step_count_aenderung] >= sent_MS_aenderung_counter ) {
            sendKNX_Multi_VOC(ms_step_count_aenderung);
            start_sent_aenderung_VOC_MS_Millis[ms_step_count_aenderung] = millis();
          }
        }
        ms_step_count_aenderung++;
        if (ms_step_count_aenderung > MAX_iButton) {
          ms_step_count_aenderung = 0;
        }



        //Alive MSG
        current_alive_msg_Millis = millis();
        if (current_alive_msg_Millis - start_alive_msg_Millis >= sent_alive_counter  && alive_msg_ON) {
          start_alive_msg_Millis = current_alive_msg_Millis;
#ifdef KDEBUG
          Debug.println(F("    ---------- send KNX Alive MSG -------"));
#endif
         Knx.write(COMOBJ_AliveMSG, true);
        }



        break;
    }

  }//ENDE KONNEKTING APPLIKATION RUNING
}
