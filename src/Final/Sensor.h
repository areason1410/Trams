#pragma once
#include "Signal.h"

class Sensor 
{
    public:
      bool state;
      int pin;
      Signal theSignal;

      Sensor(int pin, Signal theSignalIn):
      theSignal(theSignalIn)
      {
        this->pin = pin;
        this->state = false;
        pinMode(this->pin, INPUT);
      }

      bool readState() 
      {
        this->state = digitalRead(this->pin);
        return this->state;
      } 
};