#ifndef readSensor_h
#define readSensor_h

//#define KDEBUG_SensorValues_ERROR


/* #################################################################################
  //  startConvTemp()
  //  sent the order to start the temperature conversation
  // ################################################################################# */
void startConvTemp() {
  for (int i = 0 ; i < COUNT_DS18B20 ; i++) {
    DS18B20[i].startConversion_Temp();
  }
}

/* #################################################################################
  //  startConvTemp()
  //  sent the order to start the temperature conversation
  // ################################################################################# */
void startConvTemp(byte nr) {
  DS18B20[nr].startConversion_Temp();
}

/* #################################################################################
  //  startConvTemp(byte nr)
  //  sent the order to start the temperature conversation of Sensor Nr
  // ################################################################################# */
void startConvTemp_S1(byte nr) {
  DS18B20_S1[nr].startConversion_Temp();
}
void startConvTemp_S2(byte nr) {
  DS18B20_S2[nr].startConversion_Temp();
}
void startConvTemp_S3(byte nr) {
  DS18B20_S3[nr].startConversion_Temp();
}


/* #################################################################################
  //  finishConvTemp()
  //  end of temperature conversation and read the temp value
  // ################################################################################# */
void finishConvTemp() {
  for (int i = 0 ; i < COUNT_DS18B20 ; i++) {
    DS18B20[i].update_Temp();
  }
}

/* #################################################################################
  //  finishConvTemp()
  //  end of temperature conversation and read the temp value
  // ################################################################################# */
void finishConvTemp(byte nr) {
  DS18B20[nr].update_Temp();
}

/* #################################################################################
  //  finishConvTemp(byte nr)
  //  end of temperature conversation and read the temp value from Sensor NR
  // ################################################################################# */
void finishConvTemp_S1(byte nr) {
  if (CH1_active) {
    if (oneWire_CH1.checkPresence()) {
      CH1_I2C_Master_Error = false;
      if (oneWire_CH1.readStatusShortDet()) {
#ifdef KDEBUG
        Debug.println(F("CH1: 1-W Short"));
#endif
        CH1_short = true;
        oneWire_CH1.reset();
      }
      else {
        CH1_short = false;
        DS18B20_S1[nr].update_Temp();
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH1: no I2C Master"));
#endif
      CH1_I2C_Master_Error = true;
    }
  }
}
void finishConvTemp_S2(byte nr) {
  if (CH2_active) {
    DS18B20_S2[nr].update_Temp();
  }
}
void finishConvTemp_S3(byte nr) {
  if (CH3_active) {
    DS18B20_S3[nr].update_Temp();
  }
}



/* #################################################################################
  //  checkError(uint8_t nr)
  //  check all temperaturesensors which were configured in the Suite, if they are
  //  connected to the 1-Wire Bus
  // ################################################################################# */
void checkError_S1(uint8_t nr) {
  /* Section 1*/
  if (CH1_active) {
    if (DS18B20_S1[nr].isConnected() && CH1_short == false) {
      tempSensorError_S1[nr] = false;
#ifdef KDEBUG_SensorValues
      Debug.print(F("Temp-Sensor_%d:"), nr + 1);
      Debug.println(F(" %0.1f°C"), DS18B20_S1[nr].getTemp());
#endif
    }
    else {
      if (tempSensorActive_S1[nr]) {
        tempSensorError_S1[nr] = true;
#ifdef KDEBUG_SensorValues
        Debug.println(F("Temp-Sensor_%d: --.-°C"), nr + 1);
#endif
      }
      else {
#ifdef KDEBUG_SensorValues_ERROR
        Debug.println(F("Temp-Sensor_%d: ERROR"), nr + 1);
#endif
      }
    }
  }
}

void checkError_S2(uint8_t nr) {
  /* Section 2*/
  if (CH2_active) {
    if (DS18B20_S2[nr].isConnected()&& CH2_short == false) {
      tempSensorError_S2[nr] = false;
#ifdef KDEBUG_SensorValues
      Debug.print(F("Temp-Sensor_%d:"), nr + 1 + COUNT_DS18B20_S1);
      Debug.println(F(" %0.1f°C"), DS18B20_S2[nr].getTemp());
#endif
    }
    else {
      if (tempSensorActive_S2[nr]) {
        tempSensorError_S2[nr] = true;
#ifdef KDEBUG_SensorValues
        Debug.println(F("Temp-Sensor_%d: --.-°C"), nr + 1 + COUNT_DS18B20_S1);
#endif
      }
      else {
#ifdef KDEBUG_SensorValues_ERROR
        Debug.println(F("Temp-Sensor_%d: ERROR"), nr + 1 + COUNT_DS18B20_S1);
#endif
      }
    }
  }
}


void checkError_S3(uint8_t nr) {
  /* Section 3*/
  if (CH3_active) {
    if (DS18B20_S3[nr].isConnected() && CH3_short == false) {
      tempSensorError_S3[nr] = false;
#ifdef KDEBUG_SensorValues
      Debug.print(F("Temp-Sensor_%d:"), nr + 1 + COUNT_DS18B20_S1 + COUNT_DS18B20_S2);
      Debug.println(F(" %0.1f°C"), DS18B20_S3[nr].getTemp());
#endif
    }
    else {
      if (tempSensorActive_S3[nr]) {
        tempSensorError_S3[nr] = true;
#ifdef KDEBUG_SensorValues
        Debug.println(F("Temp-Sensor_%d: --.-°C"), nr + 1 + COUNT_DS18B20_S1 + COUNT_DS18B20_S2);
#endif
      }
      else {
#ifdef KDEBUG_SensorValues_ERROR
        Debug.println(F("Temp-Sensor_%d: ERROR"), nr + 1 + COUNT_DS18B20_S1 + COUNT_DS18B20_S2);
#endif
      }
    }
  }
}




/* #################################################################################
  //  printError()
  //  print out which Temperature Sensor ist not connected
  // ################################################################################# */
void printError_S1() {
  SensorError_temp_S1 = 0;
#ifdef KDEBUG_SensorValues
  Debug.print("Error S1: ");
#endif
  for (int i = 0 ; i < COUNT_DS18B20_S1 ; i++) {
#ifdef KDEBUG_SensorValues
    Debug.print(F("%d "), tempSensorError_S1[i]);
#endif
    if (tempSensorError_S1[i])
      bitSet(SensorError_temp_S1, i);
  }
  if (SensorError_temp_old_S1 != SensorError_temp_S1) {
#ifdef KDEBUG_SensorValues
    Debug.println("     KNX Temp Error S1: ");
#endif
    Knx.write(COMOBJ_ERROR_Temp_S1 , SensorError_temp_S1);
    SensorError_temp_old_S1 = SensorError_temp_S1;
  }
  else {
#ifdef KDEBUG_SensorValues
    Debug.println(" ");
#endif
  }
}

void printError_S2() {
#ifdef KDEBUG_SensorValues
  Debug.print("Error S2: ");
#endif
  for (int i = 0 ; i < COUNT_DS18B20_S2 ; i++) {
#ifdef KDEBUG_SensorValues
    Debug.print(F("%d "), tempSensorError_S2[i]);
#endif
    if (tempSensorError_S2[i])
      bitSet(SensorError_temp_S2, i);
  }
  if (SensorError_temp_old_S2 != SensorError_temp_S2) {
#ifdef KDEBUG_SensorValues
    Debug.println("     KNX Temp Error S2: ");
#endif
    Knx.write(COMOBJ_ERROR_Temp_S2 , SensorError_temp_S2);
    SensorError_temp_old_S2 = SensorError_temp_S2;
  }
  else {
#ifdef KDEBUG_SensorValues
    Debug.println(" ");
#endif
  }
}

void printError_S3() {
#ifdef KDEBUG_SensorValues
  Debug.print("Error S3: ");
#endif
  for (int i = 0 ; i < COUNT_DS18B20_S3 ; i++) {
#ifdef KDEBUG_SensorValues
    Debug.print(F("%d "), tempSensorError_S3[i]);
#endif
    if (tempSensorError_S3[i])
      bitSet(SensorError_temp_S3, i);
  }
  if (SensorError_temp_old_S3 != SensorError_temp_S3) {
#ifdef KDEBUG_SensorValues
    Debug.println("     KNX Temp Error S3: ");
#endif
    Knx.write(COMOBJ_ERROR_Temp_S3 , SensorError_temp_S3);
    SensorError_temp_old_S3 = SensorError_temp_S3;
  }
  else {
#ifdef KDEBUG_SensorValues
    Debug.println(" ");
#endif
  }
}



/* #################################################################################
  //  KNXAlarm1_HT(byte nr, bool state)
  //  sendet KNX Alarm HT
  // ################################################################################# */
void  KNXAlarm1_HT(byte nr, bool state) {
  switch (nr) {
    case 0:
      Knx.write(COMOBJ_CH1Alarm1toH, state);
      break;
    case 1:
      Knx.write(COMOBJ_CH2Alarm1toH, state);
      break;
    case 2:
      Knx.write(COMOBJ_CH3Alarm1toH, state);
      break;
  }
}
/* #################################################################################
  //  KNXAlarm1_TT(byte nr, bool state)
  //  sendet KNX Alarm HT
  // ################################################################################# */
void KNXAlarm1_TT(byte nr, bool state) {
  switch (nr) {
    case 0:
      Knx.write(COMOBJ_CH1Alarm1toL, state);
      break;
    case 1:
      Knx.write(COMOBJ_CH2Alarm1toL, state);
      break;
    case 2:
      Knx.write(COMOBJ_CH3Alarm1toL, state);
      break;
  }
}
/* #################################################################################
  //  KNXAlarm2_HT(byte nr, bool state)
  //  sendet KNX Alarm HT
  // ################################################################################# */
void KNXAlarm2_HT(byte nr, bool state) {
  switch (nr) {
    case 0:
      Knx.write(COMOBJ_CH1Alarm2toH, state);
      break;
    case 1:
      Knx.write(COMOBJ_CH2Alarm2toH, state);
      break;
    case 2:
      Knx.write(COMOBJ_CH3Alarm2toH, state);
      break;
  }
}
/* #################################################################################
  //  KNXAlarm2_TT(byte nr, bool state)
  //  sendet KNX Alarm HT
  // ################################################################################# */
void KNXAlarm2_TT(byte nr, bool state) {
  switch (nr) {
    case 0:
      Knx.write(COMOBJ_CH1Alarm2toL, state);
      break;
    case 1:
      Knx.write(COMOBJ_CH2Alarm2toL, state);
      break;
    case 2:
      Knx.write(COMOBJ_CH3Alarm2toL, state);
      break;
  }
}



/* #################################################################################
  //  checkAlarm1_HT_S1(byte nr)
  //  checkt ob ein Alarm anliegt
  // ################################################################################# */
void checkAlarm1_HT(byte nr) {
  if (isAlarm1_HT_sensors[nr] != 0 && isAlarm1_HT_aktiv[nr] == false) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 1  HT: ON"), nr + 1);
#endif
    isAlarm1_HT_aktiv[nr] = true;
    KNXAlarm1_HT(nr, true);
  }
  else if (isAlarm1_HT_sensors[nr] == 0 && isAlarm1_HT_aktiv[nr] == true) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 1  HT: OFF"), nr + 1);
#endif
    isAlarm1_HT_aktiv[nr] = false;
    KNXAlarm1_HT(nr, false);
  }
}

/* #################################################################################
  //  checkAlarm1_TT_S1()
  //  checkt ob ein Alarm anliegt
  // ################################################################################# */
void checkAlarm1_TT(byte nr) {
  if (isAlarm1_TT_sensors[nr] != 0 && isAlarm1_TT_aktiv[nr] == false) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 1  TT: ON"), nr + 1);
#endif
    isAlarm1_TT_aktiv[nr] = true;
    KNXAlarm1_TT(nr, true);
  }
  else if (isAlarm1_TT_sensors[nr] == 0 && isAlarm1_TT_aktiv[nr] == true) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 1  TT: OFF"), nr + 1);
#endif
    isAlarm1_TT_aktiv[nr] = false;
    KNXAlarm1_TT(nr, false);
  }
}

/* #################################################################################
  //  checkAlarm1_HT(byte nr)
  //  checkt ob ein Alarm anliegt
  // ################################################################################# */
void checkAlarm2_HT(byte nr) {
  if (isAlarm2_HT_sensors[nr] != 0 && isAlarm2_HT_aktiv[nr] == false) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 2  HT: ON"), nr + 1);
#endif
    isAlarm2_HT_aktiv[nr] = true;
    KNXAlarm2_HT(nr, true);
  }
  else if (isAlarm2_HT_sensors[nr] == 0 && isAlarm2_HT_aktiv[nr] == true) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 2  HT: OFF"), nr + 1);
#endif
    isAlarm2_HT_aktiv[nr] = false;
    KNXAlarm2_HT(nr, false);
  }
}
/* #################################################################################
  //  checkAlarm2_TT()
  //  checkt ob ein Alarm anliegt
  // ################################################################################# */
void checkAlarm2_TT(byte nr) {
  if (isAlarm2_TT_sensors[nr] != 0 && isAlarm2_TT_aktiv[nr] == false) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 2  TT: ON"), nr + 1);
#endif
    isAlarm2_TT_aktiv[nr] = true;
    KNXAlarm2_TT(nr, true);
  }
  else if (isAlarm2_TT_sensors[nr] == 0 && isAlarm2_TT_aktiv[nr] == true) {
#ifdef KDEBUG
    Debug.println(F("    KNX sent: CH%d: Temp Alarm 2  TT: OFF"), nr + 1);
#endif
    isAlarm2_TT_aktiv[nr] = false;
    KNXAlarm2_TT(nr, false);
  }
}


/* #################################################################################
  //  getTempvalue_S1()
  //  State maschine to read out the Sensor values from the DS18B20 Temp Sensors
  //  State1: startConTemp
  //  State2: update_Temp
  //  State3: wait
  // ################################################################################# */
bool getTempvalue() {

  switch (TempSensorState)
  {

    case startConTemp:

      /* CH1 */
      if (CH1_active) {
        if (oneWire_CH1.checkPresence()) {
          CH1_I2C_Master_Error = false;
          if (oneWire_CH1.readStatusShortDet()) {
#ifdef KDEBUG
            Debug.println(F("CH1: 1-W Short"));
#endif
            CH1_short = true;
            oneWire_CH1.reset();
          }
          else {
            CH1_short = false;
            startConvTemp_S1(step_count);
            start_conversation = millis();                                                    // start Temp converastion
            TempSensorState = wait;                                                           // jump to next state
          }
        }
        else {
#ifdef KDEBUG
          Debug.println(F("CH1: no I2C Master"));
#endif
          CH1_I2C_Master_Error = true;
        }
      }

      /* CH2 */
      if (CH2_active) {
        if (oneWire_CH2.checkPresence()) {
          CH2_I2C_Master_Error = false;
          if (oneWire_CH2.readStatusShortDet()) {
#ifdef KDEBUG
            Debug.println(F("CH2: 1-W Short"));
#endif
            CH2_short = true;
            oneWire_CH2.reset();
          }
          else {
            CH2_short = false;
            startConvTemp_S2(step_count);
            start_conversation = millis();                                                    // start Temp converastion
            TempSensorState = wait;                                                           // jump to next state
          }
        }
        else {
#ifdef KDEBUG
          Debug.println(F("CH2: no I2C Master"));
#endif
          CH2_I2C_Master_Error = true;
        }
      }

      /* CH3 */
      if (CH3_active) {
        if (oneWire_CH3.checkPresence()) {
          CH3_I2C_Master_Error = false;
          if (oneWire_CH3.readStatusShortDet()) {
#ifdef KDEBUG
            Debug.println(F("CH3: 1-W Short"));
#endif
            CH3_short = true;
            oneWire_CH3.reset();
          }
          else {
            CH3_short = false;
            startConvTemp_S3(step_count);
            start_conversation = millis();                                                    // start Temp converastion
            TempSensorState = wait;                                                           // jump to next state
          }
        }
        else {
#ifdef KDEBUG
          Debug.println(F("CH3: no I2C Master"));
#endif
          CH3_I2C_Master_Error = true;
        }
      }
      break;


    case wait:
      if ( millis() - start_conversation >= 750) {

        start_conversation = millis();

        finishConvTemp_S1(step_count);
        finishConvTemp_S2(step_count);
        finishConvTemp_S3(step_count);
#ifdef KDEBUG
        Debug.println(F("Count: %d"), step_count);
#endif
        checkError_S1(step_count);
        checkError_S2(step_count);
        checkError_S3(step_count);

        /****************************  senden bei Wertänderung  ***********************************************/
        if (DS18B20_S1[step_count].doSend_Temp()) {
#ifdef KDEBUG
          Debug.println(F("    KNX sent (w): Temp %d"), step_count + 1);
#endif
          Knx.write(COMOBJ_Tvalue1 + step_count, DS18B20_S1[step_count].getTemp());
          start_sent_aenderung_Tvalue_Millis_CH1[step_count] = millis();                                  // setzt Timer zurück für zyklisch senden bei Wertänderung
          DS18B20_S1[step_count].clearSend_Temp(); 
        }
        if (DS18B20_S2[step_count].doSend_Temp()) {
#ifdef KDEBUG
          Debug.println(F("    KNX sent (w): Temp %d"), step_count + 1 + COUNT_DS18B20_S1);
#endif
          Knx.write(COMOBJ_Tvalue15 + step_count, DS18B20_S2[step_count].getTemp());
          start_sent_aenderung_Tvalue_Millis_CH2[step_count] = millis();                                   // setzt Timer zurück für zyklisch senden bei Wertänderung
          DS18B20_S2[step_count].clearSend_Temp();
        }
        if (DS18B20_S3[step_count].doSend_Temp()) {
#ifdef KDEBUG
          Debug.println(F("    KNX sent (w): Temp %d"), step_count + 1 + COUNT_DS18B20_S1 + COUNT_DS18B20_S2);
#endif
          Knx.write(COMOBJ_Tvalue29 + step_count, DS18B20_S3[step_count].getTemp());
          start_sent_aenderung_Tvalue_Millis_CH3[step_count] = millis();                                       // setzt Timer zurück für zyklisch senden bei Wertänderung
          DS18B20_S3[step_count].clearSend_Temp();
        }

        /****************************  ALARM 1   *****************************************************/
        //Alarm1 HT CH1
        if (DS18B20_S1[step_count].getAlarm1()) {
          if (DS18B20_S1[step_count].getAlarm1_HT()) {
            bitSet(isAlarm1_HT_sensors[0], step_count);
          }
          else if (DS18B20_S1[step_count].getAlarm1_HT() == false ) {
            bitClear(isAlarm1_HT_sensors[0], step_count);
          }
          //Alarm1 TT CH1
          if (DS18B20_S1[step_count].getAlarm1_TT() && isAlarm1_TT_aktiv[0] == false) {
            bitSet(isAlarm1_TT_sensors[0], step_count);
          }
          else if (DS18B20_S1[step_count].getAlarm1_TT() == false && isAlarm1_TT_aktiv[0] == true) {
            bitClear(isAlarm1_TT_sensors[0], step_count);
          }
        }

        //Alarm HT CH2
        if (DS18B20_S2[step_count].getAlarm1()) {
          if (DS18B20_S2[step_count].getAlarm1_HT() && isAlarm1_HT_aktiv[1] == false) {
            bitSet(isAlarm1_HT_sensors[1], step_count);
          }
          else if (DS18B20_S2[step_count].getAlarm1_HT() == false && isAlarm1_HT_aktiv[1] == true) {
            bitClear(isAlarm1_HT_sensors[1], step_count);
          }
          //Alarm1 TT CH2
          if (DS18B20_S2[step_count].getAlarm1_TT() && isAlarm1_TT_aktiv[1] == false) {
            bitSet(isAlarm1_TT_sensors[1], step_count);
          }
          else if (DS18B20_S2[step_count].getAlarm1_TT() == false && isAlarm1_TT_aktiv[1] == true) {
            bitClear(isAlarm1_TT_sensors[1], step_count);
          }
        }


        //Alarm1 HT CH3
        if (CH3_active) {
          if (DS18B20_S3[step_count].getAlarm1()) {
            if (DS18B20_S3[step_count].getAlarm1_HT() && isAlarm1_HT_aktiv[2] == false) {
              bitSet(isAlarm1_HT_sensors[2], step_count);
            }
            else if (DS18B20_S3[step_count].getAlarm1_HT() == false && isAlarm1_HT_aktiv[2] == true) {
              bitClear(isAlarm1_HT_sensors[2], step_count);
            }
            //Alarm TT CH3
            if (DS18B20_S3[step_count].getAlarm1_TT() && isAlarm1_TT_aktiv[2] == false) {
              bitSet(isAlarm1_TT_sensors[2], step_count);
            }
            else if (DS18B20_S3[step_count].getAlarm1_TT() == false && isAlarm1_TT_aktiv[2] == true) {
              bitClear(isAlarm1_TT_sensors[2], step_count);
            }
          }
        }


        /****************************  ALARM 2   *****************************************************/
        //Alarm2 HT CH1
        if (DS18B20_S1[step_count].getAlarm2()) {
          if (DS18B20_S1[step_count].getAlarm2_HT() && isAlarm2_HT_aktiv[0] == false) {
            bitSet(isAlarm2_HT_sensors[0], step_count);
          }
          else if (DS18B20_S1[step_count].getAlarm2_HT() == false && isAlarm2_HT_aktiv[0] == true) {
            bitClear(isAlarm2_HT_sensors[0], step_count);
          }
          //Alarm2 TT CH1
          if (DS18B20_S1[step_count].getAlarm2_TT() && isAlarm2_TT_aktiv[0] == false) {
            bitSet(isAlarm2_TT_sensors[0], step_count);
          }
          else if (DS18B20_S1[step_count].getAlarm2_TT() == false && isAlarm2_TT_aktiv[0] == true) {
            bitClear(isAlarm2_TT_sensors[0], step_count);
          }
        }


        //Alarm HT CH2
        if (DS18B20_S2[step_count].getAlarm2()) {
          if (DS18B20_S2[step_count].getAlarm2_HT() && isAlarm2_HT_aktiv[1] == false) {
            bitSet(isAlarm2_HT_sensors[1], step_count);
          }
          else if (DS18B20_S2[step_count].getAlarm2_HT() == false && isAlarm2_HT_aktiv[1] == true) {
            bitClear(isAlarm2_HT_sensors[1], step_count);
          }
          //Alarm TT CH2
          if (DS18B20_S2[step_count].getAlarm2_TT() && isAlarm2_TT_aktiv[1] == false) {
            bitSet(isAlarm2_TT_sensors[1], step_count);
          }
          else if (DS18B20_S2[step_count].getAlarm2_TT() == false && isAlarm2_TT_aktiv[1] == true) {
            bitClear(isAlarm2_TT_sensors[0], step_count);
          }
        }


        //Alarm HT CH3
        if (CH3_active) {
          if (DS18B20_S3[step_count].getAlarm2()) {
            if (DS18B20_S3[step_count].getAlarm2_HT() && isAlarm2_HT_aktiv[2] == false) {
              bitSet(isAlarm2_HT_sensors[2], step_count);
            }
            else if (DS18B20_S3[step_count].getAlarm2_HT() == false && isAlarm2_HT_aktiv[0] == true) {
              bitClear(isAlarm2_HT_sensors[2], step_count);
            }
            //Alarm TT CH3
            if (DS18B20_S3[step_count].getAlarm2_TT() && isAlarm2_TT_aktiv[2] == false) {
              bitSet(isAlarm2_TT_sensors[2], step_count);
            }
            else if (DS18B20_S3[step_count].getAlarm2_TT() == false && isAlarm2_TT_aktiv[2] == true) {
              bitClear(isAlarm2_TT_sensors[2], step_count);
            }
          }
        }


        step_count++;                                 //zählt Step hoch für nächsten Sensor

        if (step_count >= COUNT_DS18B20_S1) {         //prüft ob alle Sensoren eingelesen wurden
          step_count = 0;

          printError_S1();
          printError_S2();
          printError_S3();

          //Alarme
          for (int i = 0 ; i < 3; i++) {
            checkAlarm1_HT(i);
            checkAlarm2_TT(i);
          }

          TempSensorState = startConTemp;
          return true;
        }
        TempSensorState = startConTemp;
      }
      break;
  }
  return false;
}




#endif
