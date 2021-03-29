#include <knx.h>
#include <Wire.h>
#include "Hardware.h"

void appSetup(uint8_t iSavePin);
void appLoop();
#ifdef WATCHDOG
#include <Adafruit_SleepyDog.h>
uint32_t gWatchdogDelay;
#endif

void setup()
{
    SerialUSB.begin(115200);
    pinMode(PROG_LED_PIN, OUTPUT);
    digitalWrite(PROG_LED_PIN, HIGH); 
    delay(DEBUG_DELAY);
    digitalWrite(PROG_LED_PIN, LOW);
    SerialUSB.println("Startup called...");
    ArduinoPlatform::SerialDebug = &SerialUSB;

#ifdef LED_YELLOW_PIN
    pinMode(LED_YELLOW_PIN, OUTPUT);
    digitalWrite(LED_YELLOW_PIN, HIGH);
#endif    

    // moved to checkBoard!!!
    // Wire.begin();
    knx.readMemory();

    // pin or GPIO the programming led is connected to. Default is LED_BUILDIN
    knx.ledPin(PROG_LED_PIN);
    // is the led active on HIGH or low? Default is LOW
    knx.ledPinActiveOn(PROG_LED_PIN_ACTIVE_ON);
    // pin or GPIO programming button is connected to. Default is 0
    knx.buttonPin(PROG_BUTTON_PIN);
    // Is the interrup created in RISING or FALLING signal? Default is RISING
    knx.buttonPinInterruptOn(PROG_BUTTON_PIN_INTERRUPT_ON);

    appSetup(SAVE_INTERRUPT_PIN);

    // start the framework.
    knx.start();
#ifdef LED_YELLOW_PIN
    digitalWrite(LED_YELLOW_PIN, LOW);
#endif
#ifdef WATCHDOG
    // use this in future for Diagnose command?
    // uint8_t lResetCause = Watchdog.resetCause();
    // setup watchdog to prevent endless loops
    int lWatchTime = Watchdog.enable(16384, false);
    SerialUSB.print("Watchdog started with a watchtime of ");
    SerialUSB.print(lWatchTime / 1000);
    SerialUSB.println(" Seconds");
#endif
}

void loop()
{
#ifdef WATCHDOG
    if (millis() - gWatchdogDelay > 1000) {
        Watchdog.reset();
        gWatchdogDelay = millis();
    }
#endif
    // don't delay here to much. Otherwise you might lose packages or mess up the timing with ETS
    knx.loop();

    // only run the application code if the device was configured with ETS
    if (knx.configured())
        appLoop();
}