#ifndef readSensorID_h
#define readSensorID_h

//#define KDEBUG_ReadID


/* #################################################################################
  //  print_Addr(byte addr[8])
  //  print the ID of the Sensor
  // ################################################################################# */
void print_Addr(byte addr[8]) {
  Debug.println(F("  ID: %02x%02x%02x%02x%02x%02x%02x%02x"), addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
}



/* #################################################################################
  //  print_New_Addr(byte addr[8])
  //  print the new ID of the Sensor
  // ################################################################################# */
void print_New_Addr(byte addr[8]) {
  Debug.println(F("  ID_new: %02x%02x%02x%02x%02x%02x%02x%02x"), addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
}





/* #################################################################################
  //  check_ID(byte ow_addr[8], byte iButton_addr[8])
  //  check if both IDs are the same
  // ################################################################################# */
bool check_ID(byte ow_addr[8], byte iButton_addr[8]) {
  //Abfrage ID von letzter Stelle, da wenn diese schon nicht übereinstimmt, dann braucht man nicht weitersuchen
  if (ow_addr[7] == iButton_addr[7]) {
    if (ow_addr[6] == iButton_addr[6]) {
      if (ow_addr[5] == iButton_addr[5]) {
        if (ow_addr[4] == iButton_addr[4]) {
          if (ow_addr[3] == iButton_addr[3]) {
            if (ow_addr[2] == iButton_addr[2]) {
              if (ow_addr[1] == iButton_addr[1]) {
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




/* #################################################################################
  //  check_oneWire_newID(byte count)
  //  check if the ID which was found on the Bus is one of the Addr which was defined
  //  in the Suite
  // ################################################################################# */
bool check_oneWire_newID(byte count) {

#ifdef KDEBUG_ReadID
  Debug.println(F("Anzahl gefunden: %d"), count);
#endif

  // löscht den speicher der IDs damit entfernte Sensoren gefunden werden können
  for (int i = 0 ; i < COUNT_DS18B20; i++) {
    newIDpos[i] = false;
#ifdef KDEBUG_ReadID
    print_Addr(new_ID_addrArray[i]);
#endif
  }

  validID = 0;
  if (count > 0) {
    for (int i = 0 ; i < count ; i++) {

      /* CH1 */
      if (readNewID_bus == 1 && CH1_active) {
        for (int n = 0; n < COUNT_DS18B20_S1 + MAX_multisenor; n++)
        {
          if (check_ID(new_ID_addrArray[i], DS18B20_address_S1[n])) {
            newIDpos[i]  = true;
            validID++;
          }
          else if (oneWire_MS_CH[n] == 1) {                                        //Frägt nur MS Sensoren ab die auch wirklich nur auf CH1 liegen
            if (check_ID(new_ID_addrArray[i], ms_DS2438_address[n])) {
              newIDpos[i]  = true;
              validID++;
            }
          }
          else {
            if (new_ID_addrArray[n][0] == 0x01) {   // IButton heraus Filtern
              newIDpos[i]  = true;
              validID++;
            }
          }
        }
      }

      /* CH2 */
      if (readNewID_bus == 2 && CH2_active) {
        for (int n = 0; n < COUNT_DS18B20_S2 + MAX_multisenor; n++)
        {
          if (check_ID(new_ID_addrArray[i], DS18B20_address_S2[n])) {
            newIDpos[i]  = true;
            validID++;
          }
          else if (oneWire_MS_CH[n] == 2) {
            if (check_ID(new_ID_addrArray[i], ms_DS2438_address[n])) {
              newIDpos[i]  = true;
              validID++;
            }
          }
          else {
            if (new_ID_addrArray[n][0] == 0x01) {   // IButton heraus Filtern
              newIDpos[i]  = true;
              validID++;
            }
          }
        }
      }

      /* CH3 */
      if (readNewID_bus == 3 && CH3_active) {
        for (int n = 0; n < COUNT_DS18B20_S3 + MAX_multisenor; n++)
        {
          if (check_ID(new_ID_addrArray[i], DS18B20_address_S3[n])) {
            newIDpos[i]  = true;
            validID++;
          }
          else if (oneWire_MS_CH[n] == 3) {
            if (check_ID(new_ID_addrArray[i], ms_DS2438_address[n])) {
              newIDpos[i]  = true;
              validID++;
            }
          }
          else {
            if (new_ID_addrArray[n][0] == 0x01) {   // IButton heraus Filtern
              newIDpos[i]  = true;
              validID++;
            }
          }
        }
      }
    }
#ifdef KDEBUG_ReadID
    Debug.println(F("Anzahl valid: %d"), validID);
#endif
    for (int i = 0; i < count; i++) {
      if (!newIDpos[i]) {
        newIdAddr[0] = new_ID_addrArray[i][0];
        newIdAddr[1] = new_ID_addrArray[i][1];
        newIdAddr[2] = new_ID_addrArray[i][2];
        newIdAddr[3] = new_ID_addrArray[i][3];
        newIdAddr[4] = new_ID_addrArray[i][4];
        newIdAddr[5] = new_ID_addrArray[i][5];
        newIdAddr[6] = new_ID_addrArray[i][6];
        newIdAddr[7] = new_ID_addrArray[i][7];
        newID = true;
      }
    }
    if (validID == count) { // dann wurde keine neue ID gefunden
      newID = false;
      firstsend = false;
#ifdef KDEBUG
      Debug.println(F("  keine neue ID gefunden"));
#endif
      return false;
    }
    else {
      if (newID)
        return true;
    }
  }
}



/* #################################################################################
  //  clearNewIdAddr()
  //  clear the last founded ID
  // ################################################################################# */
void clearNewIdAddr() {
  for (int i = 0; i < 8 ; i++) {
    newIdAddr[i] = 0;
  }
}



/* #################################################################################
  //  sent_KNX_ID()
  //  sent the new ID on the KNX BUS
  // ################################################################################# */
void sent_KNX_ID() {
  Knx.write(COMOBJ_NewID, newIdAddr);
}


/* #################################################################################
  //  sent_KNX_ID()
  //  sent the new ID on the KNX BUS
  // ################################################################################# */
byte find_Sensor() {

  counter = 0;

  // löscht den speicher der IButton IDs damit entfernte iButtons gefunden werden können
  for (int i = 0 ; i < COUNT_DS18B20; i++) {
    for (int n = 0 ; n < 8; n++) {
      new_ID_addrArray[i][n] = 0;
    }
  }
  /*  CH1 */
  if (readNewID_bus == 1 && CH1_active)
  {
    if (oneWire_CH1.checkPresence()) {
      CH1_I2C_Master_Error = false;
      if (oneWire_CH1.readStatusShortDet()) {
#ifdef KDEBUG
        Debug.println(F("CH1: 1-W Short"));
#endif
        CH1_short = true;
        oneWire_CH1.reset();
        return 0;
      }
      else {
        CH1_short = false;
        while (oneWire_CH1.search(new_ID_addrArray[counter])) {
          counter++;
        }
        oneWire_CH1.reset_search();
        if (DS2482_OneWire::crc8(new_ID_addrArray[counter], 7) != new_ID_addrArray[counter][7]) {
#ifdef KDEBUG
          Debug.println("CRC nicht korrekt!");
#endif
          return 0;
        }
        else {
          return counter;
        }
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH1: no I2C Master"));
#endif
      CH1_I2C_Master_Error = true;
    }
  }

  /*  CH2 */
  if (readNewID_bus == 2 && CH2_active)
  {
    if (oneWire_CH2.checkPresence()) { //prüft ob I2C Master ansprechbar
      CH2_I2C_Master_Error = false;
      if (oneWire_CH2.readStatusShortDet()) {
#ifdef KDEBUG
        Debug.println(F("CH2: 1-W Short"));
#endif
        CH2_short = true;
        oneWire_CH2.reset();
        return 0;
      }
      else {
        CH2_short = false;
        while (oneWire_CH2.search(new_ID_addrArray[counter])) {
          counter++;
        }
        oneWire_CH2.reset_search();
        if (DS2482_OneWire::crc8(new_ID_addrArray[counter], 7) != new_ID_addrArray[counter][7]) {
#ifdef KDEBUG
          Debug.println("CRC nicht korrekt!");
#endif
          return 0;
        }
        else {
          return counter;
        }
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH2: no I2C Master"));
#endif
      CH2_I2C_Master_Error = true;
    }
  }

  /*  CH3 */
  if (readNewID_bus == 3 && CH3_active)
  {
    if (oneWire_CH3.checkPresence()) { //prüft ob I2C Master ansprechbar
      CH3_I2C_Master_Error = false;
      if (oneWire_CH3.readStatusShortDet()) {   //prüft ob 1-W Bus "short"
#ifdef KDEBUG
        Debug.println(F("CH3: 1-W Short"));
#endif
        oneWire_CH3.reset();
        CH3_short = true;
        return 0;
      }
      else {
        CH3_short = false;
        while (oneWire_CH3.search(new_ID_addrArray[counter])) {
          counter++;
        }
        oneWire_CH3.reset_search();
        if (DS2482_OneWire::crc8(new_ID_addrArray[counter], 7) != new_ID_addrArray[counter][7]) {
#ifdef KDEBUG
          Debug.println("CRC nicht korrekt!");
#endif
          return 0;
        }
        else {
          return counter;
        }
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


/* #################################################################################
  //  searchNewID()
  //  search function to find a new Sensor on the 1-W Bus
  //  State1: searchStateOneWire
  //  State2: iButton_check
  //  State3: Sent_ID
  // ################################################################################# */
bool searchNewID() {

  if (readNewID_bus == 1 && CH1_active == true || readNewID_bus == 2 && CH2_active == true || readNewID_bus == 3 && CH3_active == true) {

    if (readNewID) {
      switch (searchIDOneWire)
      {
        case ID_search:
          countID = find_Sensor();
          searchIDOneWire = ID_check;
          //          if (countID > 0) {
          //            searchIDOneWire = ID_check;
          //          }
          break;

        case ID_check:
          if (check_oneWire_newID(countID)) {
#ifdef KDEBUG
            print_New_Addr(newIdAddr);
#endif
            if (sendNewID) {
              sent_KNX_ID();
#ifdef KDEBUG
              Debug.println("    KNX send new ID");
#endif
            }
          }
          searchIDOneWire = ID_search;
          return true;
          break;


        default:
          break;
      }
      return false;
    }
  }
}


#endif
