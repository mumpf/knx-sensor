#ifndef KNX_Message_h
#define KNX_Message_h



/* #################################################################################
  //  sendKNX_1W_CH_state()
  //  sent 1W status MSG
  // ################################################################################# */
void sendKNX_1W_CH_state() {
  Knx.write(COMOBJ_Status1WCh1, CH1_short);
  Knx.write(COMOBJ_Status1WCh2, CH2_short);
  Knx.write(COMOBJ_Status1WCh3, CH3_short);
}



/* Sent Sensor CH1          */
void sendKNX_Temp_CH1(byte nr) {
#ifdef KDEBUG_KNX
  Debug.println(F("    KNX sent(ä): Temp %d"), nr + 1);
#endif
  Knx.write(COMOBJ_Tvalue1 + nr, DS18B20_S1[nr].getTemp());
}
/* Sent Sensor CH2          */
void sendKNX_Temp_CH2(byte nr) {
#ifdef KDEBUG_KNX
  Debug.println(F("    KNX sent(ä): Temp %d"), nr + 1 + COUNT_DS18B20_S1);
#endif
  Knx.write(COMOBJ_Tvalue15 + nr, DS18B20_S2[nr].getTemp());
}
/* Sent Sensor CH3          */
void sendKNX_Temp_CH3(byte nr) {
#ifdef KDEBUG_KNX
  Debug.println(F("    KNX sent(ä): Temp %d"), nr + 1 + COUNT_DS18B20_S1 + COUNT_DS18B20_S2);
#endif
  Knx.write(COMOBJ_Tvalue29 + nr, DS18B20_S3[nr].getTemp());
}


/* #################################################################################
  //  sendKNX_Temp()
  //  sent the values of the Sensors on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 1          */
void sendKNX_Temp1() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 1");
#endif
  Knx.write(COMOBJ_Tvalue1, DS18B20[0].getTemp());
}
/* Sent Sensor 2          */
void sendKNX_Temp2() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 2");
#endif
  Knx.write(COMOBJ_Tvalue2, DS18B20[1].getTemp());
}
/* Sent Sensor 3          */
void sendKNX_Temp3() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 3");
#endif
  Knx.write(COMOBJ_Tvalue3, DS18B20[2].getTemp());
}
/* Sent Sensor 4         */
void sendKNX_Temp4() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 4");
#endif
  Knx.write(COMOBJ_Tvalue4, DS18B20[3].getTemp());
}
/* Sent Sensor 5          */
void sendKNX_Temp5() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 5");
#endif
  Knx.write(COMOBJ_Tvalue5, DS18B20[4].getTemp());
}
/* Sent Sensor 6          */
void sendKNX_Temp6() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 6");
#endif
  Knx.write(COMOBJ_Tvalue6, DS18B20[5].getTemp());
}
/* Sent Sensor 7          */
void sendKNX_Temp7() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 7");
#endif
  Knx.write(COMOBJ_Tvalue7, DS18B20[6].getTemp());
}
/* Sent Sensor 8          */
void sendKNX_Temp8() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 8");
#endif
  Knx.write(COMOBJ_Tvalue8, DS18B20[7].getTemp());
}
/* Sent Sensor 9          */
void sendKNX_Temp9() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 9");
#endif
  Knx.write(COMOBJ_Tvalue9, DS18B20[8].getTemp());
}
/* Sent Sensor 10          */
void sendKNX_Temp10() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 10");
#endif
  Knx.write(COMOBJ_Tvalue10, DS18B20[9].getTemp());
}
/* Sent Sensor 11          */
void sendKNX_Temp11() {
#ifdef KDEBUG_KNX
  Debug.println("   KNX sent: Temp 11");
#endif
  Knx.write(COMOBJ_Tvalue11, DS18B20[10].getTemp());
}
/* Sent Sensor 12          */
void sendKNX_Temp12() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 12");
#endif
  Knx.write(COMOBJ_Tvalue12, DS18B20[11].getTemp());
}
/* Sent Sensor 13          */
void sendKNX_Temp13() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 13");
#endif
  Knx.write(COMOBJ_Tvalue13, DS18B20[12].getTemp());
}
/* Sent Sensor 14         */
void sendKNX_Temp14() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 14");
#endif
  Knx.write(COMOBJ_Tvalue14, DS18B20[13].getTemp());
}
/* Sent Sensor 15          */
void sendKNX_Temp15() {
#ifdef KDEBUG_KNX
  Debug.println("  KNX sent: Temp 15");
#endif
  Knx.write(COMOBJ_Tvalue15, DS18B20[14].getTemp());
}
/* Sent Sensor 16          */
void sendKNX_Temp16() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 16");
#endif
  Knx.write(COMOBJ_Tvalue16, DS18B20[15].getTemp());
}
/* Sent Sensor 17          */
void sendKNX_Temp17() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 17");
#endif
  Knx.write(COMOBJ_Tvalue17, DS18B20[16].getTemp());
}
/* Sent Sensor 18          */
void sendKNX_Temp18() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 18");
#endif
  Knx.write(COMOBJ_Tvalue18, DS18B20[17].getTemp());
}
/* Sent Sensor 19          */
void sendKNX_Temp19() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 19");
#endif
  Knx.write(COMOBJ_Tvalue19, DS18B20[18].getTemp());
}
/* Sent Sensor 20          */
void sendKNX_Temp20() {
#ifdef KDEBUG_KNX
  Debug.println("    KNX sent: Temp 20");
#endif
  Knx.write(COMOBJ_Tvalue20, DS18B20[19].getTemp());
}


/* #################################################################################
  //  sendKNX_Temp1_5()
  //  sent only the values of the Sensors 1 - 5 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 1 - 5          */
void sendKNX_Temp1_5() {
  for (int i = 0 ; i < 5 ; i++) {
    if (DS18B20_S1[i].getisActive() && DS18B20_S1[i].isSend_Temp() == false && tempSensorError_S1[i] == false) {
      Knx.write(i + COMOBJ_Tvalue1,  DS18B20_S1[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 1 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue1);
#endif
    }
  }
}



/* #################################################################################
  //  sendKNX_Temp6_10()
  //  sent only the values of the Sensors 6 - 10 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 6 - 10          */
void sendKNX_Temp6_10() {
  for (int i = 5 ; i < 10 ; i++) {
    if (DS18B20_S1[i].getisActive() && DS18B20_S1[i].isSend_Temp() == false && tempSensorError_S1[i] == false) {
      Knx.write(i + COMOBJ_Tvalue1,  DS18B20_S1[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 1 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue1);
#endif
    }
  }
}

/* #################################################################################
  //  sendKNX_Temp11_14()
  //  sent only the values of the Sensors 11 - 14 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 11 - 14          */
void sendKNX_Temp11_14() {
  for (int i = 10 ; i < 14 ; i++) {
    if (DS18B20_S1[i].getisActive() && DS18B20_S1[i].isSend_Temp() == false && tempSensorError_S1[i] == false) {
      Knx.write(i + COMOBJ_Tvalue1,  DS18B20_S1[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 1 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue1);
#endif
    }
  }
}



/* #################################################################################
  //  sendKNX_Temp15_19()
  //  sent only the values of the Sensors 15 - 19 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 15 - 19          */
void sendKNX_Temp15_19() {
  for (int i = 0 ; i < 5 ; i++) {
    if (DS18B20_S2[i].getisActive() && DS18B20_S2[i].isSend_Temp() == false && tempSensorError_S2[i] == false) {
      Knx.write(i + COMOBJ_Tvalue15,  DS18B20_S2[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 2 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue15);
#endif
    }
  }
}

/* #################################################################################
  //  sendKNX_Temp20_24()
  //  sent only the values of the Sensors 20 - 24 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 20 - 24          */
void sendKNX_Temp20_24() {
  for (int i = 5 ; i <  10 ; i++) {
    if (DS18B20_S2[i].getisActive() && DS18B20_S2[i].isSend_Temp() == false && tempSensorError_S2[i] == false) {
      Knx.write(i + COMOBJ_Tvalue15,  DS18B20_S2[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 2 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue15);
#endif
    }
  }
}

/* #################################################################################
  //  sendKNX_Temp25_28()
  //  sent only the values of the Sensors 25 - 28 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 25 - 28          */
void sendKNX_Temp25_28() {
  for (int i = 10 ; i <  14 ; i++) {
    if (DS18B20_S2[i].getisActive() && DS18B20_S2[i].isSend_Temp() == false && tempSensorError_S2[i] == false) {
      Knx.write(i + COMOBJ_Tvalue15,  DS18B20_S2[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 2 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue15);
#endif
    }
  }
}


/* #################################################################################
  //  sendKNX_Temp29_33()
  //  sent only the values of the Sensors 29 - 33 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 29 - 33          */
void sendKNX_Temp29_33() {
  for (int i = 0 ; i < 5 ; i++) {
    if (DS18B20_S3[i].getisActive() && DS18B20_S3[i].isSend_Temp() == false && tempSensorError_S3[i] == false) {
      Knx.write(i + COMOBJ_Tvalue29,  DS18B20_S3[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 3 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue29);
#endif
    }
  }
}

/* #################################################################################
  //  sendKNX_Temp34_38()
  //  sent only the values of the Sensors 26 - 30 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 34 - 38          */
void sendKNX_Temp34_38() {
  for (int i = 5 ; i <  10 ; i++) {
    if (DS18B20_S3[i].getisActive() && DS18B20_S3[i].isSend_Temp() == false && tempSensorError_S3[i] == false) {
      Knx.write(i + COMOBJ_Tvalue29,  DS18B20_S3[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 3 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue29);
#endif
    }
  }
}

/* #################################################################################
  //  sendKNX_Temp39_42()
  //  sent only the values of the Sensors 39 - 42 on the KNX-BUS
  // ################################################################################# */
/* Sent Sensor 39 - 42          */
void sendKNX_Temp39_42() {
  for (int i = 10 ; i <  14 ; i++) {
    if (DS18B20_S3[i].getisActive() && DS18B20_S3[i].isSend_Temp() == false && tempSensorError_S3[i] == false) {
      Knx.write(i + COMOBJ_Tvalue29,  DS18B20_S3[i].getTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: Temp Section 3 = nr%d (ComObj: %d)"), i, i + COMOBJ_Tvalue29);
#endif
    }
  }
}


/* #################################################################################
  //  sendKNX_Multi_Hum()
  //  sent Hum value of the Multisensonsor
  // ################################################################################# */
void sendKNX_Multi_Hum(uint8_t nr) {
  Knx.write((nr * 4) + COMOBJ_MS1_Luftf, multiSensor[nr].getHum());
#ifdef KDEBUG_KNX
  Debug.println(F("    KNX sent(ä): MS%d: Hum"), nr + 1);
#endif
}

/* #################################################################################
  //  sendKNX_Multi_Lux()
  //  sent Hum value of the Multisensonsor
  // ################################################################################# */
void sendKNX_Multi_Lux(uint8_t nr) {
  Knx.write((nr * 4) + COMOBJ_MS1_Hellig, (uint16_t)multiSensor[nr].getLux());
#ifdef KDEBUG_KNX
  Debug.println(F("    KNX sent: MS%d: LUX"), nr + 1);
#endif
}

/* #################################################################################
  //  sendKNX_Multi_VOC()
  //  sent Hum value of the Multisensonsor
  // ################################################################################# */
void sendKNX_Multi_VOC(uint8_t nr) {
  Knx.write((nr * 4) + COMOBJ_MS1_VOC, multiSensor[nr].getVOC());
#ifdef KDEBUG_KNX
  Debug.println(F("    KNX sent(ä): MS%d: VOC"), nr + 1);
#endif
}



/* #################################################################################
  //  sendKNX_Multi()
  //  sent Temp + Hum + LUX + VOC + NTC_Temp value of the Multisensonsor
  // ################################################################################# */
void sendKNX_Multi(uint8_t nr) {

  if (multiSensor[nr].get_dev_hum() && multiSensor[nr].isSend_Hum() == false && ms_DS2438_1_Active[nr] == true) {
    Knx.write((nr * 4) + COMOBJ_MS1_Luftf, multiSensor[nr].getHum());
#ifdef KDEBUG_KNX
    Debug.println(F("    KNX sent: MS%d: Hum"), nr + 1);
#endif
  }
  if (multiSensor[nr].get_dev_lux() && multiSensor[nr].isSend_Lux() == false && ms_DS2438_1_Active[nr] == true) {
    Knx.write((nr * 4) + COMOBJ_MS1_Hellig, (uint16_t)multiSensor[nr].getLux());
#ifdef KDEBUG_KNX
    Debug.println(F("    KNX sent: MS%d: LUX"), nr + 1);
#endif
  }
  if (multiSensor[nr].get_dev_voc() && multiSensor[nr].isSend_VOC() == false && ms_DS2438_2_Active[nr] == true) {
    Knx.write((nr * 4) + COMOBJ_MS1_VOC, multiSensor[nr].getVOC());
#ifdef KDEBUG_KNX
    Debug.println(F("    KNX sent: MS%d: VOC"), nr + 1);
#endif
  }
  if (multiSensor[nr].get_dev_DS2438_Temp() && ms_DS2438_1_Active[nr] == true) {
    Knx.write((nr * 4) + COMOBJ_MS1_Temp_Int, multiSensor[nr].getTemp());                                             
#ifdef KDEBUG_KNX
    Debug.println(F("    KNX sent: MS%d: Temp_Intern"), nr + 1);
#endif
  }
  if (nr > 5) {
    if (multiSensor[nr].get_dev_ntc() && ms_DS2438_1_Active[nr] == true) {
      Knx.write(((nr - 5) * 4) + COMOBJ_MS6_Temp_NTC, multiSensor[nr].getNTCTemp());
#ifdef KDEBUG_KNX
      Debug.println(F("    KNX sent: MS%d: Temp_NTC"), nr + 1);
#endif
    }
  }
}


/* #################################################################################
  //  KNX_Sensor_msg_CH1()
  //  State maschine to send only 5 Sensors in series
  //  State1: Temp1-5
  //  State2: Temp6-10
  // ################################################################################# */
void KNX_Temp_Sensor_msg_CH1() {

  switch (stateKNXsend_CH1)
  {
    case CH1_Temp1_5:
      sendKNX_Temp1_5();
      stateKNXsend_CH1 = CH1_Temp6_10;
      break;

    case CH1_Temp6_10:
      sendKNX_Temp6_10();
      stateKNXsend_CH1 = CH1_Temp11_14;
      break;

    case CH1_Temp11_14:
      sendKNX_Temp11_14();
      stateKNXsend_CH1 = CH1_Temp1_5;
      start_sent_Tvalue_Millis_CH1 = millis();          //Setzt den Timer zum zyklisch Senden neu
      break;
  }
}

/* #################################################################################
  //  KNX_Sensor_msg_CH2()
  //  State maschine to send only 5 Sensors in series
  //  State1: Temp11-15
  //  State2: Temp16-20
  // ################################################################################# */
void KNX_Temp_Sensor_msg_CH2() {

  switch (stateKNXsend_CH2)
  {
    case CH2_Temp15_19:
      sendKNX_Temp15_19();
      stateKNXsend_CH2 = CH2_Temp20_24;
      break;

    case CH2_Temp20_24:
      sendKNX_Temp20_24();
      stateKNXsend_CH2 = CH2_Temp25_28;
      break;

    case CH2_Temp25_28:
      sendKNX_Temp25_28();
      stateKNXsend_CH2 = CH2_Temp15_19;
      start_sent_Tvalue_Millis_CH2 = millis();          //Setzt den Timer zum zyklisch Senden neu
      break;
  }
}


/* #################################################################################
  //  KNX_Sensor_msg_CH2()
  //  State maschine to send only 5 Sensors in series
  //  State1: Temp21-25
  //  State2: Temp26-30
  // ################################################################################# */
void KNX_Temp_Sensor_msg_CH3() {

  switch (stateKNXsend_CH3)
  {
    case CH3_Temp29_33:
      sendKNX_Temp29_33();
      stateKNXsend_CH3 = CH3_Temp34_38;
      break;

    case CH3_Temp34_38:
      sendKNX_Temp34_38();
      stateKNXsend_CH3 = CH3_Temp39_42;
      break;

    case CH3_Temp39_42:
      sendKNX_Temp39_42();
      stateKNXsend_CH3 = CH3_Temp29_33;
      start_sent_Tvalue_Millis_CH3 = millis();          //Setzt den Timer zum zyklisch Senden neu
      break;
  }
}

/* #################################################################################
  //  KNX_Sensor_msg()
  //  State maschine to send only 5 Sensors in series
  //  State1: Temp1-5
  //  State2: Temp6-10
  //  State3: Temp11-15
  //  State4: Temp16-20
  //  State5: Temp21-25
  //  State6: Temp26-30
  // ################################################################################# */
void KNX_Temp_Sensor_msg() {

  switch (stateKNXsend)
  {
    case Temp1_5:
      if (CH1_active) {
        sendKNX_Temp1_5();
        stateKNXsend = Temp6_10;
      }
      else
        stateKNXsend = Temp15_19;
      break;

    case Temp6_10:
      sendKNX_Temp6_10();
      stateKNXsend = Temp11_14;
      break;

    case Temp11_14:
      sendKNX_Temp11_14();
      stateKNXsend = Temp15_19;
      break;

    case Temp15_19:
      if (CH2_active) {
        sendKNX_Temp15_19();
        stateKNXsend = Temp20_24;
      }
      else {
        stateKNXsend = Temp29_33;
      }
      break;

    case Temp20_24:
      sendKNX_Temp20_24();
      stateKNXsend = Temp25_28;
      break;

    case Temp25_28:
      sendKNX_Temp25_28();
      stateKNXsend = Temp29_33;
      break;


    case Temp29_33:
      if (CH3_active) {
        sendKNX_Temp29_33();
        stateKNXsend = Temp34_38;
      }
      else {
        stateKNXsend = Temp1_5;
        initalSend = false;
      }
      break;

    case Temp34_38:
      sendKNX_Temp34_38();
      stateKNXsend = Temp39_42;
      break;

    case Temp39_42:
      sendKNX_Temp39_42();
      initalSend = false;                           //damit nur einmal am Anfang alle Werte gesendet werden
      stateKNXsend = Temp1_5;
      break;
  }
}

void KNX_Multi_Sensor_msg() {

  switch (ms_stateKNXsend)
  {
    case MultiS_1:
      if (CH3_active && oneWire_MS_CH[0] == 3  || CH2_active && oneWire_MS_CH[0] == 2 || CH1_active && oneWire_MS_CH[0] == 1)
        sendKNX_Multi(0);
      ms_stateKNXsend = MultiS_2;
      break;

    case MultiS_2:
      if (CH3_active && oneWire_MS_CH[1] == 3  || CH2_active && oneWire_MS_CH[1] == 2 || CH1_active && oneWire_MS_CH[1] == 1)
        sendKNX_Multi(1);
      ms_stateKNXsend = MultiS_3;
      break;

    case MultiS_3:
      if (CH3_active && oneWire_MS_CH[2] == 3  || CH2_active && oneWire_MS_CH[2] == 2 || CH1_active && oneWire_MS_CH[2] == 1)
        sendKNX_Multi(2);
      ms_stateKNXsend = MultiS_4;
      break;

    case MultiS_4:
      if (CH3_active && oneWire_MS_CH[3] == 3  || CH2_active && oneWire_MS_CH[3] == 2 || CH1_active && oneWire_MS_CH[3] == 1)
        sendKNX_Multi(3);
      ms_stateKNXsend = MultiS_5;
      break;

    case MultiS_5:
      if (CH3_active && oneWire_MS_CH[4] == 3  || CH2_active && oneWire_MS_CH[4] == 2 || CH1_active && oneWire_MS_CH[4] == 1)
        sendKNX_Multi(4);
      ms_stateKNXsend = MultiS_6;
      break;

    case MultiS_6:
      if (CH3_active && oneWire_MS_CH[5] == 3  || CH2_active && oneWire_MS_CH[5] == 2 || CH1_active && oneWire_MS_CH[5] == 1)
        sendKNX_Multi(5);
      ms_stateKNXsend = MultiS_7;
      break;

    case MultiS_7:
      if (CH3_active && oneWire_MS_CH[6] == 3  || CH2_active && oneWire_MS_CH[6] == 2 || CH1_active && oneWire_MS_CH[6] == 1)
        sendKNX_Multi(6);
      ms_stateKNXsend = MultiS_8;
      break;

    case MultiS_8:
      if (CH3_active && oneWire_MS_CH[7] == 3  || CH2_active && oneWire_MS_CH[7] == 2 || CH1_active && oneWire_MS_CH[7] == 1)
        sendKNX_Multi(7);
      ms_stateKNXsend = MultiS_9;
      break;

    case MultiS_9:
      if (CH3_active && oneWire_MS_CH[8] == 3  || CH2_active && oneWire_MS_CH[8] == 2 || CH1_active && oneWire_MS_CH[8] == 1)
        sendKNX_Multi(8);
      ms_stateKNXsend = MultiS_10;
      break;

    case MultiS_10:
      if (CH3_active && oneWire_MS_CH[9] == 3  || CH2_active && oneWire_MS_CH[9] == 2 || CH1_active && oneWire_MS_CH[9] == 1)
        sendKNX_Multi(9);
      start_sent_Multi_Millis = millis();  
      ms_stateKNXsend = MultiS_1;
      break;
  }
}


#endif
