void setTimer(){

// Enable clock for TC 
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 ); // wait for sync 

  // The type cast must fit with the selected timer mode 
  TcCount16* TC = (TcCount16*) TC3; // get timer struct

  TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;   // Disable TCx
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 

  TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;  // Set Timer counter Mode to 16 bits
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 
  TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ; // Set TC as normal Normal Frq
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 

  TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024;   // Set perscaler
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 
  
  //TC->PER.reg = 0xFF;   // Set counter Top using the PER register but the 16/32 bit timer counts allway to max  
  // while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 

  //TC->CC[0].reg = 0x1d5;               //  ================>   10ms Timer Takt
  //TC->CC[0].reg = 0x2f;                //  ================>    1ms Timer Takt
  //setTimer_ms(10);
  //while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 
  
  // Interrupts 
  TC->INTENSET.reg = 0;            // disable all interrupts
  //TC->INTENSET.bit.OVF = 1;        // enable overfollow
  TC->INTENSET.bit.MC0 = 1;          // enable compare match to CC0

  // Enable InterruptVector
  NVIC_EnableIRQ(TC3_IRQn);

  // Enable TC
  TC->CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 

}

void setTimer_ms(int value){
  // The type cast must fit with the selected timer mode 
  TcCount16* TC = (TcCount16*) TC3; // get timer struct
  float system_clock = 1/(48000000/1024.0);
  TC->CC[0].reg = value/system_clock/1000;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync 
}

