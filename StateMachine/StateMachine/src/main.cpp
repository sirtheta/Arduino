#include <Arduino.h>
#include <blink.h>
#include "NRF52_MBED_TimerInterrupt.h"

#define INTERVAL 5000
#define BLINK_INTERVAL_ORANGE 500

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);


enum State
{
  Open,
  Closing,
  Closed,
  Opening
};

struct Input
{
  bool barrierOpen;
  bool barrierClosed;
  bool trainpassed;
  bool trainApproaching;
};

State currentState = Open;
Input input = Input {false, false,false,false};

void Open_f()
{
  blinkOrange(50);
  if (input.trainApproaching)
  {
    currentState = Closing;
  }
}

void Closing_f()
{
  blinkOrange(100);
  if (input.barrierClosed)
  {
    currentState = Closed;
  }
}

void Closed_f()
{
  blinkOrange(300);
  if (input.trainpassed)
  {
    currentState = Opening;
  }
}

void Opening_f()
{
  blinkOrange(1000);
  if (input.barrierOpen)
  {
    currentState = Open;
  }
}

void timerHandler() 
{
  switch (currentState)
  {
  case Open:
      input = Input{false,false,false,true};
    break;
  case Closing:
    input = Input{false, true, false, false};
    break;
  case Closed:
    input = Input{false, false, true, false};
    break;
  case Opening:
    input = Input{true, false, false, false};
    break;

  default:
    break;
  }
}

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  ITimer.attachInterruptInterval(INTERVAL * 1000, timerHandler);
  // put your setup code here, to run once:
}

void loop() 
{
  Serial.println(currentState);

  switch (currentState)
  {
    case Open:
      Open_f();
      break;
    case Closing:
      Closing_f();
      break;
    case Closed:
      Closed_f();
      break;
    case Opening:
      Opening_f();
      break;

    default:
      break;
  }
}