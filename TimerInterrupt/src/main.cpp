#include <Arduino.h>
#include "NRF52_MBED_TimerInterrupt.h"

#define TIMER_INTERVAL_MS 30
#define SENSOR_VALUE 4.89

void toggle_blinking();
void timerHandler(); 
void blink();
void getSensorValue();
void debugRoutine();

const uint8_t BUTTON_PIN = 3;
bool buttonPressed = false;
bool bBlink = false;
int counter = 0;
float sensorValue;
float frequency;

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggle_blinking, FALLING);
}

void loop()
{
  getSensorValue();
  if (bBlink)
  {
    blink();
  }
}

void getSensorValue()
{
  //reading value from poti
  //float sensorValue = analogRead(A0) * (5.0 / 1023.0);
  sensorValue = SENSOR_VALUE;
  frequency = 1 / (1.875 * sensorValue + 0.8125) * 1000;
}
  
void blink()
{
  if (sensorValue < 0.1)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    Serial.print("Led is always off!");
  }
  else if (sensorValue > 4.9)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Led is always on!");
    delay(1000);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(frequency);
    digitalWrite(LED_BUILTIN, LOW);
    delay(frequency);
  }
  //debugRoutine();
}

void debugRoutine()
{
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" ");
  Serial.print("SensorValue: ");
  Serial.print(sensorValue);
  Serial.println(" ");
  Serial.println("counter: ");
  Serial.println(counter);
}

//this method gets called if one presses the button. See setup--> attachInterrupt
void toggle_blinking()
{
  buttonPressed = true;
  ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, timerHandler);
}

void timerHandler()
{  
  if (buttonPressed)
  {
    counter += 1;
  }    
  if (counter > 5)
  {
    counter = 0;
    buttonPressed = false;
    bBlink = !bBlink;
    ITimer.detachInterrupt();
  }    
}