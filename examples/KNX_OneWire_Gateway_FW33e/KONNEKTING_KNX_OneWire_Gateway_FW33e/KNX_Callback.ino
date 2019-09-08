// Callback function to handle com objects updates
void knxEvents(byte index) {

  switch (index)
  {
    case COMOBJ_iBstatusReq:
      iButtonRequest = true;
      iButton_State_send = true;
      break;

    case COMOBJ_iBLED_SW_CH1:
      Knx.read(COMOBJ_iBLED_SW_CH1, stateLEDiButton[0]);
      setLEDiButton[0] = true;
      break;

    case COMOBJ_iBLED_SW_CH2:
      Knx.read(COMOBJ_iBLED_SW_CH2, stateLEDiButton[1]);
      setLEDiButton[1] = true;
      break;

    case COMOBJ_iBLED_SW_CH3:
      Knx.read(COMOBJ_iBLED_SW_CH3, stateLEDiButton[2]);
      setLEDiButton[2] = true;
      break;

    case COMOBJ_iBLED_SW_CH4:
      Knx.read(COMOBJ_iBLED_SW_CH1, stateLEDiButton[3]);
      setLEDiButton[3] = true;
      break;

    case COMOBJ_iBLED_SW_CH5:
      Knx.read(COMOBJ_iBLED_SW_CH5, stateLEDiButton[4]);
      setLEDiButton[4] = true;
      break;

    case COMOBJ_iBLED_SW_CH6:
      Knx.read(COMOBJ_iBLED_SW_CH6, stateLEDiButton[5]);
      setLEDiButton[5] = true;
      break;

    case COMOBJ_iBLED_SW_CH7:
      Knx.read(COMOBJ_iBLED_SW_CH7, stateLEDiButton[6]);
      setLEDiButton[6] = true;
      break;

    case COMOBJ_iBLED_SW_CH8:
      Knx.read(COMOBJ_iBLED_SW_CH8, stateLEDiButton[7]);
      setLEDiButton[7] = true;
      break;



    default: break;
  }
};
