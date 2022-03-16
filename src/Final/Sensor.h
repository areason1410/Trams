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
      int index;
      Signal* theSignal = nullptr;

      /**
       * @brief Construct a new Sensor object
       * 
       * @param pin Pin number for the sensor
       * @param theSignalIn Signal that is "paired" with the sensor
       * @param index Index in the sensor array (Just for saving computing time)
       */
      Sensor(int pin, Signal theSignalIn, int index)
      {
        this->pin = pin;
        this->state = false;
        this->theSignal = &theSignalIn;
        this->index = index;
        pinMode(this->pin, INPUT);
      }

      /**
       * @brief Gets the state of the sensor
       * 
       * @return state
       */
      bool readState() 
      {
        this->state = 1 - digitalRead(this->pin);
        return this->state;
      } 

      /**
       * @brief Get the direction the sensor is indicating for
       * 
       * @return Signal->signalDirection
       */
      Direction getDirection()
      {
          return theSignal->signalDirection;
      }

      /**
       * @brief Update function to be called each iteration in the main loop
       * 
       */
      void update()
      {
          readState();
          if(state == 1)
          {
              theSignal->changeState(0);
          }
          else
          {
              theSignal->changeState(1);
          }
      }

};

/**
 * @brief Array of sensors
 * 
 */
Sensor sensorArray[2] =
{
    Sensor(IRL1, signalArray[0], 0),
    Sensor(IRR1, signalArray[1], 1)
};