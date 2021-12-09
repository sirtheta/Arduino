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

void blinkOrange(float frequency)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisLedBuiltIn >= frequency)
  {
    // save the last time you blinked the LED
    previousMillisLedBuiltIn = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (iLedBuiltInState == LOW)
    {
      iLedBuiltInState = HIGH;
    }
    else
    {
      iLedBuiltInState = LOW;
    }
    digitalWrite(LED_BUILTIN, iLedBuiltInState);
  }
}

void blinkRGB(float intervalLedR, float intervalLedG, float intervalLedB)
{
  unsigned long currentMillisL1 = millis();
  if (currentMillisL1 - previousMillisLed1 >= intervalLedR)
  {
    // save the last time you blinked the LED
    previousMillisLed1 = currentMillisL1;

    // if the LED is off turn it on and vice-versa:
    if (iLed1State == LOW)
    {
      iLed1State = HIGH;
    }
    else
    {
      iLed1State = LOW;
    }
    digitalWrite(LEDR, iLed1State);
  }

  unsigned long currentMillisL2 = millis();
  if (currentMillisL2 - previousMillisLed2 >= intervalLedG)
  {
    // save the last time you blinked the LED
    previousMillisLed2 = currentMillisL2;

    // if the LED is off turn it on and vice-versa:
    if (iLed2State == LOW)
    {
      iLed2State = HIGH;
    }
    else
    {
      iLed2State = LOW;
    }
    digitalWrite(LEDG, iLed2State);
  }

  unsigned long currentMillisL3 = millis();
  if (currentMillisL3 - previousMillisLed3 >= intervalLedB)
  {
    // save the last time you blinked the LED
    previousMillisLed3 = currentMillisL3;

    // if the LED is off turn it on and vice-versa:
    if (iLed3State == LOW)
    {
      iLed3State = HIGH;
    }
    else
    {
      iLed3State = LOW;
    }
    digitalWrite(LEDB, iLed3State);
  }
}