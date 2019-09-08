#ifndef MULTISENSOR_h
#define MULTISENSOR_h

#include "OneWire_Multisensor.h"


/* #################################################################################
  //  print_Addr(byte addr[8])
  //  print the ID of the Sensor
  // ################################################################################# */
void print_Multisensor_Addr(byte addr[8]) {
  Debug.print(F("ID: %02x%02x%02x%02x%02x%02x%02x%02x"), addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
}

// ################################################
// ### Debug Print Multisensor Device
// ################################################
/*
   HUM             = 1
   VOC             = 2
   VOC + HUM       = 3
   HUM + LUX       = 5
   VOC + LUX       = 6
   VOC + HUM + LUX = 7
   LUX + NTC       = 20
   VOC + LUX + NTC = 22
   LUX + LUX + NTC = 28
   HUM + intern Temp = 33
*/
void print_Multisensor_Device1(byte device) {
  switch (device) {
    case 1:
      Debug.println(F("HUM"));
      break;
    case 3:
      Debug.println(F("HUM"));
      break;
    case 5:
      Debug.println(F("HUM + LUX"));
      break;
    case 6:
      Debug.println(F("LUX"));
      break;
    case 7:
      Debug.println(F("HUM + LUX"));
      break;
    case 20:
      Debug.println(F("LUX + NTC"));
      break;
    case 22:
      Debug.println(F("LUX + NTC"));
      break;
    case 28:
      Debug.println(F("LUX + NTC"));
      break;
    case 33:
      Debug.println(F("Hum(+ interner Temp-Sensor)"));
      break;
    default:
      Debug.println(F("kein Sensor ausgewählt"));
      break;
  }
}

// ################################################
// ### Debug Print Multisensor Device
// ################################################
/*
   HUM             = 1
   VOC             = 2
   VOC + HUM       = 3
   HUM + LUX       = 5
   VOC + LUX       = 6
   VOC + HUM + LUX = 7
   LUX + NTC       = 20
   VOC + LUX + NTC = 22
   LUX + LUX + NTC = 28
*/
void print_Multisensor_Device2(byte device) {
  switch (device) {
    case 2:
      Debug.println(F("VOC"));
      break;
    case 3:
      Debug.println(F("VOC"));
      break;
    case 6:
      Debug.println(F("VOC"));
      break;
    case 7:
      Debug.println(F("VOC"));
      break;
    case 22:
      Debug.println(F("VOC"));
      break;
    case 28:
      Debug.println(F("2.LUX"));
      break;
    default:
      Debug.println(F("kein Sensor ausgewält"));
      break;
  }
}


bool is_1W_CH1_ready() {
  if (oneWire_MS_CH[ms_DS2438_step_count] == 1 && CH1_active) {
    if (oneWire_CH1.checkPresence()) {
      CH1_I2C_Master_Error = false;
      if (oneWire_CH1.readStatusShortDet()) {
#ifdef KDEBUG
        Debug.println(F("CH1: 1-W Short MS"));
#endif
        CH1_short = true;
        oneWire_CH1.reset();
        return false;
      }
      else {
        CH1_short = false;
        return true;
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH1: no I2C Master"));
#endif
      CH1_I2C_Master_Error = true;
      return false;
    }
  }
  else {
    return false;
  }
}


bool is_1W_CH2_ready() {
  if (oneWire_MS_CH[ms_DS2438_step_count] == 2 && CH2_active) {
    if (oneWire_CH2.checkPresence()) {
      CH2_I2C_Master_Error = false;
      if (oneWire_CH2.readStatusShortDet()) {
#ifdef KDEBUG
        Debug.println(F("CH2: 1-W Short MS"));
#endif
        CH2_short = true;
        oneWire_CH2.reset();
        return false;
      }
      else {
        CH2_short = false;
        return true;
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH2: no I2C Master"));
#endif
      CH2_I2C_Master_Error = true;
      return false;
    }
  }
  else {
    return false;
  }
}


bool is_1W_CH3_ready() {
  if (oneWire_MS_CH[ms_DS2438_step_count] == 3 && CH3_active) {
    if (oneWire_CH3.checkPresence()) {
      CH3_I2C_Master_Error = false;
      if (oneWire_CH3.readStatusShortDet()) {
#ifdef KDEBUG
        Debug.println(F("CH3: 1-W Short MS"));
#endif
        CH3_short = true;
        oneWire_CH3.reset();
        return false;
      }
      else {
        CH3_short = false;
        return true;
      }
    }
    else {
#ifdef KDEBUG
      Debug.println(F("CH3: no I2C Master"));
#endif
      CH3_I2C_Master_Error = true;
      return false;
    }
  }
  else {
    return false;
  }
}

/* #################################################################################
  //  Multisensor_DS2438()
  //  read values of all Multisensors togehter
  // ################################################################################# */
bool Multisensor_DS2438() {

  switch (Read_DS2438_Sensor)
  {
    // read Temp
    case startCon_DS2438_Temp:

      /*  CH1   */
      if (is_1W_CH1_ready()) {
        if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
          multiSensor[ms_DS2438_step_count].startConversion_DS2438_Temp();
        if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
          multiSensor[ms_DS2438_step_count].startConversion_DS2438_Temp_CH2();
        ms_start_conversation = millis();
        Read_DS2438_Sensor = startCon_DS2438_ADC;
      }
      /*  CH2   */
      else if (is_1W_CH2_ready()) {
        if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
          multiSensor[ms_DS2438_step_count].startConversion_DS2438_Temp();
        if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
          multiSensor[ms_DS2438_step_count].startConversion_DS2438_Temp_CH2();
        ms_start_conversation = millis();
        Read_DS2438_Sensor = startCon_DS2438_ADC;
      }
      /*  CH3   */
      else if (is_1W_CH3_ready()) {
        if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
          multiSensor[ms_DS2438_step_count].startConversion_DS2438_Temp();
        if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
          multiSensor[ms_DS2438_step_count].startConversion_DS2438_Temp_CH2();
        ms_start_conversation = millis();
        Read_DS2438_Sensor = startCon_DS2438_ADC;
      }
      else {
        ms_DS2438_step_count++;     // bei Short sprung zum nächsten Sensor
        if (ms_DS2438_step_count >= MAX_iButton) {
          ms_DS2438_step_count = 0;
          return true;
        }
        return false;
      }
      break;


    // read ADC (VDD)
    case startCon_DS2438_ADC:
      if ( millis() - ms_start_conversation >= 10) {

        if (is_1W_CH1_ready()) {
          if (multiSensor[ms_DS2438_step_count ].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor =  update_DS2438_VDD;
        }
        else if (is_1W_CH2_ready()) {
          if (multiSensor[ms_DS2438_step_count ].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor =  update_DS2438_VDD;
        }
        else if (is_1W_CH3_ready()) {
          if (multiSensor[ms_DS2438_step_count ].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor =  update_DS2438_VDD;
        }
        else {
          Read_DS2438_Sensor =  startCon_DS2438_Temp;
        }
      }
      break;


    // get VDD DS2438
    case update_DS2438_VDD:
      if ( millis() - ms_start_conversation >= 5) {

        if (is_1W_CH1_ready()) {
          if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].startConversion_DS2438_VDD();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].startConversion_DS2438_VDD_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor = re_startCon_DS2438_ADC;
        }
        else if (is_1W_CH2_ready()) {
          if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].startConversion_DS2438_VDD();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].startConversion_DS2438_VDD_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor = re_startCon_DS2438_ADC;
        }
        else if (is_1W_CH3_ready()) {
          if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].startConversion_DS2438_VDD();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].startConversion_DS2438_VDD_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor = re_startCon_DS2438_ADC;
        }
        else {
          Read_DS2438_Sensor =  startCon_DS2438_Temp;
        }
      }
      break;



    case re_startCon_DS2438_ADC:
      if ( millis() - ms_start_conversation >= 5) {

        if (is_1W_CH1_ready()) {
          if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor = update_DS2438_VAD;
        }
        else if (is_1W_CH2_ready()) {
          if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor = update_DS2438_VAD;
        }
        else if (is_1W_CH3_ready()) {
          if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC();
          if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
            multiSensor[ms_DS2438_step_count].re_startConversion_DS2438_ADC_CH2();
          ms_start_conversation = millis();
          Read_DS2438_Sensor = update_DS2438_VAD;
        }
        else {
          Read_DS2438_Sensor =  startCon_DS2438_Temp;
        }
      }
      break;


    case update_DS2438_VAD:
      if ( millis() - ms_start_conversation >= 5) {
        
        if (multiSensor[ms_DS2438_step_count].get_dev_hum() || multiSensor[ms_DS2438_step_count].get_dev_lux())
          multiSensor[ms_DS2438_step_count].update();
        if (multiSensor[ms_DS2438_step_count].get_dev_voc() || multiSensor[ms_DS2438_step_count].get_dev_lux2())
          multiSensor[ms_DS2438_step_count].update_CH2();


        /****************************  senden bei Wertänderung  ***********************************************/
        // HUM
        if (multiSensor[ms_DS2438_step_count].doSend_Hum()) {
#ifdef KDEBUG
          Debug.println(F("    KNX sent HUM(ä): MS %d"), ms_DS2438_step_count + 1);
#endif
          Knx.write((ms_DS2438_step_count * 4) + COMOBJ_MS1_Luftf, multiSensor[ms_DS2438_step_count].getHum());
          start_sent_aenderung_HUM_MS_Millis[ms_DS2438_step_count] = millis();                                  // setzt Timer zurück für zyklisch senden bei Wertänderung
          multiSensor[ms_DS2438_step_count].clearSend_Hum();
        }
        // LUX
        if (multiSensor[ms_DS2438_step_count].doSend_Lux()) {
#ifdef KDEBUG
          Debug.println(F("    KNX sent Lux(ä): MS %d"), ms_DS2438_step_count + 1);
#endif
          Knx.write((ms_DS2438_step_count * 4) + COMOBJ_MS1_Hellig, (uint16_t)multiSensor[ms_DS2438_step_count].getLux());
          start_sent_aenderung_LUX_MS_Millis[ms_DS2438_step_count] = millis();                                  // setzt Timer zurück für zyklisch senden bei Wertänderung
          multiSensor[ms_DS2438_step_count].clearSend_Lux();
        }
        // VOC
        if (multiSensor[ms_DS2438_step_count].doSend_VOC()) {
#ifdef KDEBUG
          Debug.println(F("    KNX sent VOC(ä): MS %d"), ms_DS2438_step_count + 1);
#endif
          Knx.write((ms_DS2438_step_count * 4) + COMOBJ_MS1_VOC, multiSensor[ms_DS2438_step_count].getVOC());
          start_sent_aenderung_VOC_MS_Millis[ms_DS2438_step_count] = millis();                                  // setzt Timer zurück für zyklisch senden bei Wertänderung
          multiSensor[ms_DS2438_step_count].clearSend_VOC();
        }

 
#ifdef KDEBUG
        Debug.println(F("Count_MS_2438: %d"), ms_DS2438_step_count);
#endif
#ifdef KDEBUG_MultiSensoren
        if (multiSensor[ms_DS2438_step_count].getisActive_DS2438_1() ||  multiSensor[ms_DS2438_step_count].getisActive_DS2438_2() )
        {
          switch (multiSensor[ms_DS2438_step_count].getDevice()) {

            /* HUM               = 1
               VOC               = 2
               VOC + HUM         = 3
               HUM + LUX         = 5
               VOC + LUX         = 6
               VOC + HUM + LUX   = 7
               LUX + NTC         = 20
               VOC + LUX + NTC   = 22
               LUX + LUX + NTC   = 28
               HUM + intern Temp = 33 */

            case 1:
              Debug.println(F("Multisensor_%d: %d prozent"), ms_DS2438_step_count + 1, multiSensor[ms_DS2438_step_count].getHum());
              break;

            case 2:
              Debug.println(F("Multisensor_%d: %dppm"), ms_DS2438_step_count + 1, multiSensor[ms_DS2438_step_count].getVOC() );
              break;

            case 3:
              Debug.println(F("Multisensor_%d: %0.0f prozent - %dppm"), ms_DS2438_step_count + 1, multiSensor[ms_DS2438_step_count].getHum(), multiSensor[ms_DS2438_step_count].getVOC() );
              break;

            case 5:
              Debug.println(F("Multisensor_%d: %0.0fLUX  - %0.0f prozent "), ms_DS2438_step_count + 1,  multiSensor[ms_DS2438_step_count].getLux() ,  multiSensor[ms_DS2438_step_count].getHum() );
              break;

            /* VOC + LUX*/
            case 6:
              Debug.println(F("Multisensor_%d: %0.0fLUX  -  %dppm"), ms_DS2438_step_count + 1,  multiSensor[ms_DS2438_step_count].getLux() ,   multiSensor[ms_DS2438_step_count].getVOC() );
              break;

            /* VOC + HUM + LUX  */
            case 7:
              Debug.println(F("Multisensor_%d: %0.0fLUX  - %0.0f prozent   -  %dppm"), ms_DS2438_step_count + 1,  multiSensor[ms_DS2438_step_count].getLux() ,  multiSensor[ms_DS2438_step_count].getHum() ,   multiSensor[ms_DS2438_step_count].getVOC() );
              break;

            /* LUX + NTC */
            case 20:
              Debug.println(F("Multisensor_%d: %0.0fLUX  - %0.1f°C"), ms_DS2438_step_count + 1,  multiSensor[ms_DS2438_step_count].getLux() ,  multiSensor[ms_DS2438_step_count].getNTCTemp() );
              break;

            /* VOC + LUX + NTC */
            case 22:
              Debug.println(F("Multisensor_%d: %0.0fLUX  - %0.1f°C  -  %dppm"), ms_DS2438_step_count + 1,  multiSensor[ms_DS2438_step_count].getLux() ,  multiSensor[ms_DS2438_step_count].getNTCTemp(),  multiSensor[ms_DS2438_step_count].getVOC() );
              break;

            case 28:
              Debug.println(F("Multisensor_%d: %0.0fLUX  - %0.0f prozent  2. %0.0fLUX  "), ms_DS2438_step_count + 1,  multiSensor[ms_DS2438_step_count].getLux() ,  multiSensor[ms_DS2438_step_count].getHum(), multiSensor[ms_DS2438_step_count].getLux2() );
              break;

            case 33:
              Debug.println(F("Multisensor_%d: %0.1f°C - %0.0f prozent "), ms_DS2438_step_count + 1, multiSensor[ms_DS2438_step_count].getTemp(),  multiSensor[ms_DS2438_step_count].getHum() );
              break;

          }
        }
#endif
        ms_DS2438_step_count++;

        if (ms_DS2438_step_count >= MAX_iButton) {
          ms_DS2438_step_count = 0;
          Read_DS2438_Sensor = startCon_DS2438_Temp;
          return true;
        }
        Read_DS2438_Sensor = startCon_DS2438_Temp;

      }
      break;
  }
  return false;
}



#endif
