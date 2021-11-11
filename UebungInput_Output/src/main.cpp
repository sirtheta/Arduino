#include <Arduino.h>

float voltage = 3;
float frequency;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  frequency = 1/(1.875 * voltage + 0.8125)*1000;
}

void loop() {
  if (voltage < 0.1)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    Serial.print("Led is always off!");
  }
  else if (voltage > 4.9)
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
  Serial.print(frequency);
  }  
}