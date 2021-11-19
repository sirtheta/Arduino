#include <Arduino.h>

const uint8_t BUTTON_PIN = 3;
void toggle_blinking();
bool buttonPressed = false;

//Example with reading the volt value from a poti and have an interrupt with a button attached to pin 3

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  //Attaches the intterupt and calls the method(second Parameter)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggle_blinking, FALLING);
}

void loop()
{
  if (buttonPressed)
  {
    Serial.println("Button was Pressd!");
    
    //reading value from poti
    float sensorValue = analogRead(A0) * (5.0 / 1023.0); 
    
    //calculate the value to have 1Hz at 0.1V and 10Hz at 4.9V
    float frequency = 1 / (1.875 * sensorValue + 0.8125) * 1000; 
    
    //Turn LED off if value is below 0.1V
    if (sensorValue < 0.1)
    {
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      Serial.print("Led is always off!");
    }
    //LED is always on if value is above 4.9V
    else if (sensorValue > 4.9)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("Led is always on!");
      delay(1000);
    }
    //Blink led in the calculated frequency
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

//this method gets called if one presses the button. See setup--> attachInterrupt
void toggle_blinking()
{
  buttonPressed = !buttonPressed;
}