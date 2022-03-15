#pragma once
#include "Signal.h"


const byte IRL1 = 12;
const byte IRL2 = 2;
const byte IRR1 = 3;
const byte IRR2 = 4;

byte IRArray[4] = {IRL1, IRL2, IRR1, IRR2};

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

      Direction getDirection()
      {
          return theSignal.signalDirection;
      }

      void update()
      {
          readState();
          if(state == 1)
          {
              theSignal.changeState(0);
          }
          else
          {
              theSignal.changeState(1);
          }
      }
};


Sensor sensorArray[2] =
{
    Sensor(IRL1, signalArray[0]),
    Sensor(IRR1, signalArray[1])
};