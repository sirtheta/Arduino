#include <Arduino.h>

//storage for intervals
unsigned long previousMillisLedBuiltIn = 0;
unsigned long previousMillisLed1 = 0;
unsigned long previousMillisLed2 = 0;
unsigned long previousMillisLed3 = 0;

//LED States
int iLedBuiltInState = LOW;
int iLed1State = LOW;
int iLed2State = LOW;
int iLed3State = LOW;

void toggle(int pin, int state)
{
  state = state == LOW ? HIGH : LOW;
  digitalWrite(pin, state);
}

void blinkOrange(float frequency)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisLedBuiltIn >= frequency)
  {
    // save the last time you blinked the LED
    previousMillisLedBuiltIn = currentMillis;
    toggle(LED_BUILTIN, iLedBuiltInState);
  }
}

void blinkRGB(float intervalLedR, float intervalLedG, float intervalLedB)
{
  void blinkR(float intervalLedR);
  void blinkG(float intervalLedG);
  void blinkB(float intervalLedB);
}

void blinkR(float intervalLedR)
{
  unsigned long currentMillisL1 = millis();
  if (currentMillisL1 - previousMillisLed1 >= intervalLedR)
  {
    // save the last time you blinked the LED
    previousMillisLed1 = currentMillisL1;
    toggle(LEDR, iLed1State);
  }
}

void blinkG(float intervalLedG)
{
  unsigned long currentMillisL2 = millis();
  if (currentMillisL2 - previousMillisLed2 >= intervalLedG)
  {
    // save the last time you blinked the LED
    previousMillisLed2 = currentMillisL2;
    toggle(LEDG, iLed2State);
  }
}

void blinkB(float intervalLedB)
{
  unsigned long currentMillisL3 = millis();
  if (currentMillisL3 - previousMillisLed3 >= intervalLedB)
  {
    // save the last time you blinked the LED
    previousMillisLed3 = currentMillisL3;
    toggle(LEDB, iLed3State);
  }
}
