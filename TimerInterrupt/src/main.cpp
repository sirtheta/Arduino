#include <Arduino.h>
#include "NRF52_MBED_TimerInterrupt.h"
#include "blink.h"
#include "defines.h"

//define methods
void toggle_blinking();
void timerHandler();
void debounce();
void blink(float sensorValue, float frequency);
void blinkRGB(float interval1, float interval2, float interval3);
void getSensorValue();

const uint8_t BUTTON_PIN = 3;

volatile bool buttonPressed = false;
volatile bool bBlink = false;
volatile int counter = 0;

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

  //Switch off RGB LED's, why are they inverted?!
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggle_blinking, FALLING);
  ITimer.attachInterruptInterval(DEBOUNCE_INTERVAL * 1000, timerHandler);
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
  blinkRGB(interval1, interval2, interval3);
}

//this method gets called if one presses the button. See setup--> attachInterrupt
void toggle_blinking()
{
  buttonPressed = true;
}

void timerHandler()
{
  debounce();
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

void debounce()
{
  if (buttonPressed)
  {
    counter++;
    if (counter > 5)
    {
      counter = 0;
      buttonPressed = false;
      bBlink = !bBlink;
    }
  }
}