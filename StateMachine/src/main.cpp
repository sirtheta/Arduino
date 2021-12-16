#include <Arduino.h>
#include <blink.h>
#include "NRF52_MBED_TimerInterrupt.h"

#define INTERVAL 5000
#define CLOSING_OPENING_TIME 5000
#define BLINK_INTERVAL_ORANGE 500
#define DEBOUNCE_INTERVAL 40

const uint8_t BUTTON_PIN = 4;
bool buttonPressed = false;
bool bTimerRunning = false;
bool bDetach = false;
int iCounter = 0;

NRF52_MBED_Timer ITimerDebounce(NRF_TIMER_3);
NRF52_MBED_Timer ITimer2(NRF_TIMER_4);

enum State
{
  OPEN,
  CLOSING,
  CLOSED,
  OPENING
};

struct Input
{
  bool barrierOpen;
  bool barrierClosed;
  bool trainPassed;
  bool trainApproaching;
};

State currentState = OPEN;
Input input = Input {false, false,false,false};

void switchState()
{
  switch (currentState)
  {
  case OPEN:
      input = Input{false,false,false,true};
    break;
  case CLOSING:
      input = Input{false, true, false, false};
    break;
  case CLOSED:
      input = Input{false, false, true, false};
    break;
  case OPENING:
      input = Input{true, false, false, false};
    break;

  default:
    break;
  }
  bDetach = true;
}
/******************************************/
/* used when doing the blinking with timer*/
/******************************************/

// void timerHandler() 
// {
//   switchState();
// }
/******************************************/

//Debouncemethod for the button
void debounce()
{
  if (buttonPressed)
  {
    iCounter++;
    if (iCounter > 5)
    {
      iCounter = 0;
      switchState();
      ITimerDebounce.detachInterrupt();
      buttonPressed = false;
    }
  }
}

void buttonInterrupt()
{
  if (!bTimerRunning)
  {
    buttonPressed = true;
    ITimerDebounce.attachInterruptInterval(DEBOUNCE_INTERVAL * 1000, debounce);    
  }  
}

void openingClosing(State state)
{
  if (!bTimerRunning)
  {
    ITimer2.attachInterruptInterval(CLOSING_OPENING_TIME * 1000, switchState);
    //switch off OrangeLed
    digitalWrite(LED_BUILTIN, LOW);
    bTimerRunning = true;
  } 
  if (state == CLOSING)
  {
    blinkR(40);
  }
  else if (state == OPENING)
  {
    blinkG(40);
  }  
}

/********************************************************************************************/
/* Setup and Loop Section                                                                    */
/********************************************************************************************/
void setup() 
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  //ITimerDebounce.attachInterruptInterval(INTERVAL * 1000, timerHandler);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, FALLING);
}

void loop() 
{
  if (bDetach)
  {
    ITimer2.detachInterrupt();
    bTimerRunning = false;
    bDetach = false;
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
  }
  
  switch (currentState)
    {
    case OPEN:
      blinkOrange(50);
      if (input.trainApproaching)
      {
        currentState = CLOSING;
      }
      break;
    case CLOSING:
      openingClosing(CLOSING);
      if (input.barrierClosed)
      {
        currentState = CLOSED;
      }
      break;
    case CLOSED:
      blinkOrange(300);
      if (input.trainPassed)
      {
        currentState = OPENING;
      }
      break;
    case OPENING:
      openingClosing(OPENING);
      if (input.barrierOpen)
      {
        currentState = OPEN;
      }
      break;

    default:
      break;
  }
}