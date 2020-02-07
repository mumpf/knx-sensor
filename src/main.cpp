#include <knx.h>
#include <Wire.h>

// #define BOARD_DEVEL 1
#define BOARD_BERKER 1
// ################################################
// ### IO Configuration
// ################################################
#ifdef BOARD_DEVEL
#define PROG_LED_PIN 26
#define PROG_LED_PIN_ACTIVE_ON LOW
#define PROG_BUTTON_PIN 10
#define PROG_BUTTON_PIN_INTERRUPT_ON RISING
#define SAVE_INTERRUPT_PIN 0
#define BUZZER_PIN 0
#endif
#ifdef BOARD_BERKER
#define PROG_LED_PIN 13
#define PROG_LED_PIN_ACTIVE_ON HIGH
#define PROG_BUTTON_PIN 11
#define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
#define SAVE_INTERRUPT_PIN 8 // A2 // 8
#define BUZZER_PIN 9
#define LED_YELLOW_PIN 38
#endif
void appSetup(uint8_t iBuzzerPin, uint8_t iSavePin);
void appLoop();

void setup()
{
    SerialUSB.begin(115200);
    pinMode(PROG_LED_PIN, OUTPUT);
    digitalWrite(PROG_LED_PIN, HIGH); 
    delay(10000);
    digitalWrite(PROG_LED_PIN, LOW);
    SerialUSB.println("Startup called...");
    ArduinoPlatform::SerialDebug = &SerialUSB;

#ifdef LED_YELLOW_PIN
    pinMode(LED_YELLOW_PIN, OUTPUT);
    digitalWrite(LED_YELLOW_PIN, HIGH);
#endif    

    Wire.begin();    
    knx.readMemory();

    // pin or GPIO the programming led is connected to. Default is LED_BUILDIN
    knx.ledPin(PROG_LED_PIN);
    // is the led active on HIGH or low? Default is LOW
    knx.ledPinActiveOn(PROG_LED_PIN_ACTIVE_ON);
    // pin or GPIO programming button is connected to. Default is 0
    knx.buttonPin(PROG_BUTTON_PIN);
    // Is the interrup created in RISING or FALLING signal? Default is RISING
    knx.buttonPinInterruptOn(PROG_BUTTON_PIN_INTERRUPT_ON);

    // print values of parameters if device is already configured
    if (knx.configured())
        appSetup(BUZZER_PIN, SAVE_INTERRUPT_PIN);

    // start the framework.
    knx.start();
#ifdef LED_YELLOW_PIN
    digitalWrite(LED_YELLOW_PIN, LOW);
#endif
}

void loop()
{
    // don't delay here to much. Otherwise you might lose packages or mess up the timing with ETS
    knx.loop();

    // only run the application code if the device was configured with ETS
    if (knx.configured())
        appLoop();
}