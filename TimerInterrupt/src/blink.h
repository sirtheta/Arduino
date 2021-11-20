#include <Arduino.h>
#include "defines.h"

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

void blink(float sensorValue, float frequency)
{
  if (sensorValue < 0.1)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (sensorValue > 4.9)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
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
}

void blinkRGB(float interval1, float interval2, float interval3)
{
  unsigned long currentMillisL1 = millis();
  if (currentMillisL1 - previousMillisLed1 >= interval1)
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
    digitalWrite(led1, iLed1State);
  }

  unsigned long currentMillisL2 = millis();
  if (currentMillisL2 - previousMillisLed2 >= interval2)
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
    digitalWrite(led2, iLed2State);
  }

  unsigned long currentMillisL3 = millis();
  if (currentMillisL3 - previousMillisLed3 >= interval3)
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
    digitalWrite(led3, iLed3State);
  }
}