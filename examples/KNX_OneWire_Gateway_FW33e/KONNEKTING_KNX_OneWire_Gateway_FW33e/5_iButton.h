#ifndef iButton_h
#define iButton_h

#include "DS2482_OneWire.h"

#define DS2408_CHANNEL_WRITE_CMD 0x5A
#define DS2408_CHANNEL_READ_CMD  0xF5



void iButton_state() {
  bool state = false;
  for (byte i = 0; i < MAX_iButton; i++) {
    if (iButtonActive[i]) {
      if (iButtonState[i] != iButtonLastState[i]) {
        if (iButtonInvOutput[i])
          state = !iButtonState[i];
        else
          state = iButtonState[i];
#ifdef KDEBUG
        Debug.println(F("  Send iButton%d: state: %d  ComObj: %d"), i + 1, state, iButtonComObj[i]);
#endif
        Knx.write(iButtonComObj[i], state);
        iButtonLastState[i] = iButtonState[i];
      }
    }
  }
}


/*--------------------------------------------------------------------------------------------------------*/
/*
  /*   KNX Botschaften iButtons
  /*
  /*--------------------------------------------------------------------------------------------------------*/

void iButton_KNX_send (byte nr) {
  Knx.write(iButtonComObj[nr], iButtonState[nr]);
}



bool all_absent() {
  bool absent = true;
  for (byte i = 0; i < MAX_iButton; i++) {
    if (iButtonActive[i]) {
      if (iButtonState[i]) {
        absent = false;
        //                Debug.println(F("not absent: iButton %d"),i);
      }
    }
  }
  return absent;
}

bool all_present() {
  bool present = true;
  for (byte i = 0; i < MAX_iButton; i++) {
    if (iButtonActive[i]) {
      if (!iButtonState[i]) {
        present = false;
        //                Debug.println(F("present: iButton %d"),i);
      }
    }
  }
  return present;
}




void iButton_allAnwesend() {
  bool tmp_present = all_present();
  if (tmp_present != lastState_present) {
    if (tmp_present) {
#ifdef KDEBUG
      Debug.println("  Send message: all iButtons are present");
#endif
      Knx.write(COMOBJ_allAnw, true);
    }
    else {
#ifdef KDEBUG
      Debug.println("  Send message: at least one of iButtons is absent");
#endif
      Knx.write(COMOBJ_allAnw, false);
    }
    lastState_present = tmp_present;
  }
}


void iButton_allAbwesend() {

  switch (state_iButtonAbw)
  {
    case wait_allAbw:

      if (iButton_allAbw_delay) {
        start_delay_Abw_Millis = millis();
#ifdef KDEBUG
        Debug.println("  Abwesenheit delay ... start");
#endif
        state_iButtonAbw = wait_delay;
      }
      else {
        state_iButtonAbw = sendAllAbw;
      }
      break;

    case wait_delay:

      current_delay_Abw_Millis = millis();
      if ( current_delay_Abw_Millis - start_delay_Abw_Millis >= delay_counter) {
        state_iButtonAbw = sendAllAbw;
      }
      break;

    case sendAllAbw:
#ifdef KDEBUG
      Debug.println("  Send message: alle iButtons abwesend");
#endif
      if (allAbw_B_S == 1) {
        Knx.write(COMOBJ_allAbw_bool, true);
      }
      if (allAbw_B_S == 2) {
        Knx.write(COMOBJ_allAbw_Szene, szenenWahl);
      }
      state_iButtonAbw = stopAbw;
      delayAbgelaufen = true;
      break;

    case stopAbw:
      break;
  }
}


void KNX_iButtons_msg() {

  /*  bei Statusänderung KNX MSG senden */
  iButton_state();

  /*  prüft ob alle Anwesend */
  if (allAnwSend) {
    iButton_allAnwesend();
  }

  /*  prüft ob alle Abwesend */
  if ( allAbw_B_S > 0) {
    if (all_absent()) {
      if (firstAbsentSet == false) {
        state_iButtonAbw = wait_allAbw;         // Wenn alle Abwesend wird delay gestartet
        firstAbsentSet = true;
      }
    }
    else {
      if (!delayAbgelaufen) {
        state_iButtonAbw = stopAbw;             // Wird wieder ein iButton erkannt bevor delay abgelaufen -> delay wird gestopt
        firstAbsentSet = false;
      }
      else {
        if (allAbw_B_S == 1) {
          Knx.write(COMOBJ_allAbw_bool, false);
        }
        delayAbgelaufen = false;
      }
    }
    iButton_allAbwesend();
  }
  /* ENDE Prüfung ob alle Abwesend */



  if (iButton_State_send == true) {
    static uint8_t count = 0;
    iButton_KNX_send (count);
    count++;
    if (count == MAX_iButton) {
      iButton_State_send = false;
      count = 0;
    }
  }
}





bool check_iButton(byte ow_addr[8], byte iButton_addr[8]) {

  //Abfrage ID von letzter Stelle, da wenn diese schon nicht übereinstimmt, dann braucht man nicht weitersuchen
  if (ow_addr[7] == iButton_addr[7]) {
    if (ow_addr[1] == iButton_addr[6]) {
      if (ow_addr[2] == iButton_addr[5]) {
        if (ow_addr[3] == iButton_addr[4]) {
          if (ow_addr[4] == iButton_addr[3]) {
            if (ow_addr[5] == iButton_addr[2]) {
              if (ow_addr[6] == iButton_addr[1]) {
                if (ow_addr[0] == iButton_addr[0]) {
                  return true;
                }
                else
                  return false;
              }
              else
                return false;
            }
            else
              return false;
          }
          else
            return false;
        }
        else
          return false;
      }
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}




void printiButtonState (bool state[10]) {
  Debug.println(F("  Unreg iButtons: %d"), iButton_unreg_count);
  Debug.println(F("  %d%d%d%d%d%d%d%d%d%d"), state[0], state[1], state[2], state[3], state[4], state[5], state[6], state[7], state[8], state[9]);
}



void print_iButton(byte addr[8]) {
  Debug.println(F("  %02x%02x%02x%02x%02x%02x%02x%02x"), addr[0], addr[6], addr[5], addr[4], addr[3], addr[2], addr[1], addr[7]);
}


void print_reg_iButton(byte addr[8]) {
  Debug.println(F("  %02x%02x%02x%02x%02x%02x%02x%02x"), addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
}




void unregistered_iButtons(byte counter) {

  if (infoWrongID) {
    Knx.write(COMOBJ_iButtonUnregID, true);
  }

  for (int i = 0; i < counter; i++) {
#ifdef KDEBUG
    Debug.println(F("  Not registered iButton was found!"));
    print_iButton(iButton_unreg_addr_Array[counter]);
#endif

    if (sendinfoWrongID) {
      byte tmp[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      tmp[0] = iButton_unreg_addr_Array[counter][0];
      tmp[1] = iButton_unreg_addr_Array[counter][6];
      tmp[2] = iButton_unreg_addr_Array[counter][5];
      tmp[3] = iButton_unreg_addr_Array[counter][4];
      tmp[4] = iButton_unreg_addr_Array[counter][3];
      tmp[5] = iButton_unreg_addr_Array[counter][2];
      tmp[6] = iButton_unreg_addr_Array[counter][1];
      tmp[7] = iButton_unreg_addr_Array[counter][7];
      Knx.write(COMOBJ_iButtonSendunregID, tmp);
    }
  }
}




bool iButtonIsConnected (byte iButton_nr) {

#ifdef KDEBUG_iButton_search
  Debug.println(F("  Sate iButton_%d: %d  1):%d  2):%d  3):%d"), iButton_nr + 1 , iButtonState[iButton_nr], iButtonListArray[0][iButton_nr], iButtonListArray[1][iButton_nr], iButtonListArray[2][iButton_nr]);
#endif

  if (iButtonListArray[0][iButton_nr] == false && iButtonListArray[1][iButton_nr] == false && iButtonListArray[2][iButton_nr] == false && iButtonListArray[3][iButton_nr] == false && iButtonListArray[4][iButton_nr] == false   ) {
    return false;
  }
  else
  {
    return true;
  }
}




void check_oneWire_iButtons(byte iButton_count, byte loop_count) {

  if (!iButton_search_error) {
    //löscht alle Zustände und Fragt anschließen alle Zustände wieder ab -> So wird erkannt on ein Button nicht mehr angeschlossen ist
    for (int d = 0 ; d < MAX_iButton ; d++) {
      iButtonListArray[loop_count][d] = false;
    }
  }

  if (iButton_count > 0) {
    for (int i = 0 ; i < iButton_count ; i++) {
      if (check_iButton(iButton_addrArray[i], iButton0)) {
        iButtonState[0] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][0] = true;
      }
      else if (check_iButton(iButton_addrArray[i], iButton1)) {
        iButtonState[1] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][1] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton2)) {
        iButtonState[2] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][2] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton3)) {
        iButtonState[3] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][3] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton4)) {
        iButtonState[4] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][4] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton5)) {
        iButtonState[5] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][5] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton6)) {
        iButtonState[6] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][6] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton7)) {
        iButtonState[7] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[loop_count][7] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton8)) {
        iButtonState[8] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][8] = true;
      }
      else if  (check_iButton(iButton_addrArray[i], iButton9)) {
        iButtonState[9] = true;
        for (int i = 0 ; i < checkSteps ; i++)
          iButtonListArray[i][9] = true;
      }
      else {
        if (iButton_addrArray[i][0] == 0x01) {   //NUR IButton bewerten
          iButton_unreg_count++;
          for (int n = 0; n < 8; n++) {
            iButton_unreg_addr_Array[iButton_unreg_count][n] = iButton_addrArray[i][n] ;
          }
        }
      }
    }

    if ( iButton_count != iButton_count_old) {
#ifdef KDEBUG
      Debug.println(F("  found %dx iButtons"), iButton_count);
#endif
    }

    if ( iButton_unreg_count != iButton_unreg_count_old) {
      iButton_unreg_det = false;
    }

    if (iButton_unreg_count > 0) {
      if (iButton_unreg_det == false) {
        unregistered_iButtons(iButton_unreg_count);
        iButton_unreg_det = true;
      }
    }
    else {
      iButton_unreg_det = false;
    }
  }

  iButton_count_old = iButton_count;
  iButton_count = 0;
  iButton_unreg_count_old = iButton_unreg_count;
  iButton_unreg_count = 0;

}




void check_oneWire_iButtons_Group1() {
  uint16_t temp = 0;
  uint16_t temp1 = 0;

  for (int i = 0; i < MAX_iButton; i++) {
    temp |= ( iButtonState[i] << i);
  }

  temp1 = AbwGruppe1 & temp;

  if (AbwGruppe1 == temp1 && iButtonGroup1_det == false) {
    iButtonGroup1_det = true;
    Knx.write(COMOBJ_AnwGr1, true);
#ifdef KDEBUG
    Debug.println(F("  Send iButton: Group1 = True"));
#endif
  }
  else if (AbwGruppe1 != temp1 && iButtonGroup1_det == true) {
    iButtonGroup1_det = false;
    Knx.write(COMOBJ_AnwGr1, false);
#ifdef KDEBUG
    Debug.println(F("  Send iButton: Group1 = False"));
#endif
  }

}



void check_oneWire_iButtons_Group2() {
  uint16_t temp = 0;
  uint16_t temp2 = 0;

  for (int i = 0; i < MAX_iButton; i++) {
    temp |= ( iButtonState[i] << i);
  }

  temp2 = AbwGruppe2 & temp;

  if (AbwGruppe2 == temp2 && iButtonGroup2_det == false) {
    iButtonGroup2_det = true;
    Knx.write(COMOBJ_AnwGr2, true);
#ifdef KDEBUG
    Debug.println(F("  Send iButton: Group2 = True"));
#endif
  }
  else if (AbwGruppe2 != temp2 && iButtonGroup2_det == true) {
    iButtonGroup2_det = false;
    Knx.write(COMOBJ_AnwGr2, false);
#ifdef KDEBUG
    Debug.println(F("  Send iButton: Group2 = False"));
#endif
  }

}

void check_oneWire_iButtons_Group3() {
  uint16_t temp = 0;
  uint16_t temp3 = 0;

  for (int i = 0; i < MAX_iButton; i++) {
    temp |= ( iButtonState[i] << i);
  }

  temp3 = AbwGruppe3 & temp;

  if (AbwGruppe3 == temp3 && iButtonGroup3_det == false) {
    iButtonGroup3_det = true;
    Knx.write(COMOBJ_AnwGr3, true);
#ifdef KDEBUG
    Debug.println(F("  Send iButton: Group3 = True"));
#endif
  }
  else if (AbwGruppe3 != temp3 && iButtonGroup3_det == true) {
    iButtonGroup3_det = false;
    Knx.write(COMOBJ_AnwGr3, false);
#ifdef KDEBUG
    Debug.println(F("  Send iButton: Group3 = False"));
#endif
  }

}



/*--------------------------------------------------------------------------------------------------------*/
/*
  /*   Search iButtons
  /*
  /*--------------------------------------------------------------------------------------------------------*/


byte search_oneWire_iButtons() {

  static uint8_t counter = 0;                   // Anzahl der gefundenen 1-Wire device
  uint8_t iButton_count = 0;                    // Anzahl der gefundenen iButtons

  // löscht den speicher der IButton IDs damit entfernte iButtons gefunden werden können
  for (int i = 0 ; i < MAX_iButton; i++) {
    for (int n = 0 ; n < 8; n++) {
      iButton_addrArray[i][n] = 0;
    }
  }

  /********  CH1   *******************************************************************************/
  if (readiButton_bus == 1) {
    if (oneWire_CH1.checkPresence()) {
      CH1_I2C_Master_Error = false;
      if (oneWire_CH1.readStatusShortDet()) {   // Prüft on der 1-Wire Bus einen Short to GND aufweißt.
#ifdef KDEBUG
        Debug.println(F("**SD_1**"));
#endif
        CH1_short = true;
        oneWire_CH1.reset();
        iButton_search_error = true;
        return 0;
      }
      else {
        CH1_short = false;
        // Wenn keine SD erkannt wurde: Such-Scheife die so oft durchlaufen wird wie 1-WIre device gefunden werden
        while (oneWire_CH1.search(iButton_addrArray[counter])) {
          Knx.task();
          if (DS2482_OneWire::crc8( iButton_addrArray[counter], 7) != iButton_addrArray[counter][7]) {
            iButton_search_error = true;
#ifdef KDEBUG
            Debug.println(F("CRC is not valid!"));
#endif
            return 0;
          }
          else {
            oneWire_CH1.reset();
            if (iButton_addrArray[counter][0] == 0x01) {   //NUR IButton bewerten
              iButton_count++;
            }
            counter++;
          }
        }
        counter = 0;
        oneWire_CH1.reset_search();

#ifdef KDEBUG_iButton_search
        for (int i = 0 ; i < iButton_count ; i++) {
          print_iButton(iButton_addrArray[i]);
        }
        Debug.println(F("---"));
#endif

        iButton_search_error = false;

        return iButton_count;
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH1: no I2C Master"));
#endif
      CH1_I2C_Master_Error = true;
    }
  }

  /********  CH2   *******************************************************************************/
  if (readiButton_bus == 2) {
    if (oneWire_CH2.checkPresence()) {
      CH2_I2C_Master_Error = false;
      if (oneWire_CH2.readStatusShortDet()) {   // Prüft on der 1-Wire Bus einen Short to GND aufweißt.
#ifdef KDEBUG
        Debug.println(F("**SD_2**"));
#endif
        oneWire_CH2.reset();
        iButton_search_error = true;
        CH2_short = true;
        return 0;
      }
      else {
        CH2_short = false;
        // Wenn keine SD erkannt wurde: Such-Scheife die so oft durchlaufen wird wie 1-WIre device gefunden werden
        while (oneWire_CH2.search(iButton_addrArray[counter])) {
          Knx.task();
          if (DS2482_OneWire::crc8( iButton_addrArray[counter], 7) != iButton_addrArray[counter][7]) {
            iButton_search_error = true;
#ifdef KDEBUG
            Debug.println(F("CRC is not valid!"));
#endif
            return 0;
          }
          else {
            oneWire_CH2.reset();
            if (iButton_addrArray[counter][0] == 0x01) {   //NUR IButton bewerten
              iButton_count++;
            }
            counter++;
          }
        }
        counter = 0;
        oneWire_CH2.reset_search();

#ifdef KDEBUG_iButton_search
        for (int i = 0 ; i < iButton_count ; i++) {
          print_iButton(iButton_addrArray[i]);
        }
        Debug.println(F("---"));
#endif

        iButton_search_error = false;

        return iButton_count;
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH2: no I2C Master"));
#endif
      CH2_I2C_Master_Error = true;
    }
  }
  /********  CH3   *******************************************************************************/
  if (readiButton_bus == 3) {
    if (oneWire_CH3.checkPresence()) {
      CH3_I2C_Master_Error = false;
      if (oneWire_CH3.readStatusShortDet()) {   // Prüft on der 1-Wire Bus einen Short to GND aufweißt.
#ifdef KDEBUG
        Debug.println(F("**SD_3**"));
#endif
        oneWire_CH3.reset();
        iButton_search_error = true;
        CH3_short = true;
        return 0;
      }
      else {
        CH3_short = false;
        // Wenn keine SD erkannt wurde: Such-Scheife die so oft durchlaufen wird wie 1-WIre device gefunden werden
        while (oneWire_CH3.search(iButton_addrArray[counter])) {
          Knx.task();
          if (DS2482_OneWire::crc8( iButton_addrArray[counter], 7) != iButton_addrArray[counter][7]) {
            iButton_search_error = true;
#ifdef KDEBUG
            Debug.println(F("CRC is not valid!"));
#endif
            return 0;
          }
          else {
            oneWire_CH3.reset();
            if (iButton_addrArray[counter][0] == 0x01) {   //NUR IButton bewerten
              iButton_count++;
            }
            counter++;
          }
        }
        counter = 0;
        oneWire_CH3.reset_search();

#ifdef KDEBUG_iButton_search
        for (int i = 0 ; i < iButton_count ; i++) {
          print_iButton(iButton_addrArray[i]);
        }
        Debug.println(F("---"));
#endif

        iButton_search_error = false;

        return iButton_count;
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH3: no I2C Master"));
#endif
      CH3_I2C_Master_Error = true;
    }
  }
}




/*--------------------------------------------------------------------------------------------------------*/
/*
  /*   State Maschine
  /*
  /*--------------------------------------------------------------------------------------------------------*/
void find_iButton() {

  static uint8_t loop_counter = 0;
  static uint8_t iButton_sent_count = 0;

  if (readiButton_bus == 1 && CH1_active == true || readiButton_bus == 2 && CH2_active == true || readiButton_bus == 3 && CH3_active == true) {

    switch (iButtonStateOneWire)
    {

      case iButton_search:
        check_oneWire_iButtons(search_oneWire_iButtons(), loop_counter);      // sucht IButton und Prüft ob diese regisriert sind
        loop_counter++;

        if (loop_counter >= checkSteps) {
          loop_counter = 0;
        }
        for (int i = 0 ; i < MAX_iButton; i++) {
          iButtonState[i] = iButtonIsConnected(i);                            // uppdate liste welche iButton erkannt wurden
        }
        KNX_iButtons_msg();
        //iButton_KNX_send (iButton_sent_count);
        iButton_sent_count++;
        if (iButton_sent_count > MAX_iButton) {
          iButton_sent_count = 0;
          iButtonRequest = false;
        }
        //iButtonStateOneWire = iButton_status; //
        break;


      //    case iButton_check:
      //      //KNX_iButtons_msg();
      //      if (!iButtonRequest)
      //        iButtonStateOneWire = iButton_search;
      //      else
      //        iButtonStateOneWire = iButton_status;
      //      break;


      case iButton_status:
        //iButton_KNX_send (iButton_sent_count);
        iButton_sent_count++;
        if (iButton_sent_count > MAX_iButton) {
          iButton_sent_count = 0;
          iButtonRequest = false;
        }
        iButtonStateOneWire = iButton_search;
        break;

    }

    for (int i = 0; i < 8 ; i++) {
      if (setLEDiButton[i]) {
        DS2408_SW.set_LED_DS2408(i, stateLEDiButton[i]);                                      
        setLEDiButton[i] = false;
#ifdef KDEBUG
        Debug.println(F("  ----  LED%d  update -----"), i + 1);
#endif
      }
    }
  }
}



#endif
