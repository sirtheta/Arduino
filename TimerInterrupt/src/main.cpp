#include <Arduino.h>
#include "NRF52_MBED_TimerInterrupt.h"
#include "defines.h"

const uint8_t BUTTON_PIN = 3;
void toggle_blinking();
bool buttonPressed = false;


// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);


void TimerHandler(void)
{
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggle_blinking, FALLING);
  ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler);

}

void loop()
{
  if (buttonPressed)
  {
    Serial.println("Button was Pressd!");
    
    float sensorValue = analogRead(A0) * (5.0 / 1023.0);
    float frequency = 1 / (1.875 * sensorValue + 0.8125) * 1000;
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
      Serial.print("Frequency: ");
      Serial.print(frequency);
      Serial.println(" ");
      Serial.print("Voltage: ");
      Serial.print(sensorValue);
    }
  }

void toggle_blinking()
{
  buttonPressed = !buttonPressed;
}