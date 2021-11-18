#include <Arduino.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop()
{
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
    Serial.print("Next: ");
    Serial.print(frequency);
    Serial.print(" ");
    Serial.print("Voltage: ");
    Serial.print(sensorValue);
}