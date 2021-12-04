#include <Arduino.h>
#include "NRF52_MBED_TimerInterrupt.h"
#include "blink.h"
#include "defines.h"

//define methods
void buttonInterrupt();
void timerHandler();
void blink(float sensorValue, float frequency);
void blinkRGB(float interval1, float interval2, float interval3);
void getSensorValue();
void rgbAllOff();

const uint8_t BUTTON_PIN = 4;

volatile bool buttonPressed = false;
volatile bool bBlink = false;
volatile bool bBlinkRgb = false;
volatile int iCounter = 0;
volatile int iBlinkRgb = 0;

float sensorValue;
float frequency;
float interval1 = 0;
float interval2 = 0;
float interval3 = 0;


// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  rgbAllOff();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, FALLING);
}

void loop()
{
  getSensorValue();
  if (bBlink)
  {
    blink(sensorValue, frequency);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  if (bBlinkRgb)
  {        
    blinkRGB(interval1, interval2, interval3);
  } 
  else
  {
    rgbAllOff();
  }   
}

//this method gets called if one presses the button. See setup--> attachInterrupt
void buttonInterrupt()
{
  buttonPressed = true;
  ITimer.attachInterruptInterval(DEBOUNCE_INTERVAL * 1000, timerHandler);
}

void timerHandler()
{
    if (buttonPressed)
  {
    iCounter++;
    if (iCounter > 5)
    {
      iCounter = 0;
      iBlinkRgb++;
      bBlink = !bBlink;

      if (iBlinkRgb == 3)
      {
        iBlinkRgb = 0;
        bBlinkRgb = !bBlinkRgb;
      }
      
      ITimer.detachInterrupt();
      buttonPressed = false;
    }
  }
}

void rgbAllOff()
{
  //Switch off RGB LED's, why are they inverted?!
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}

void getSensorValue()
{
  //reading value from poti
  //float sensorValue = analogRead(A0) * (5.0 / 1023.0);
  sensorValue = SENSOR_VALUE;
  frequency = 1 / (1.875 * sensorValue + 0.8125) * 1000;
  interval1 = frequency * 4;
  interval2 = frequency * 2;
  interval3 = frequency * 1.5;
}