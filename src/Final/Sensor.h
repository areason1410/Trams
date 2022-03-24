#pragma once
#include "Signal.h"


const byte IRL1 = 2;
const byte IRL2 = 12;
const byte IRR1 = 3;
const byte IRR2 = 4;

byte IRArray[4] = {IRL1, IRL2, IRR1, IRR2};

class StationSensor
{
    public:
      bool state;
      int pin;
      int index;
      Direction direction;
      // Signal* theSignal = nullptr;

      /**
       * @brief Construct a new Sensor object
       * 
       * @param pin Pin number for the sensor
       * @param theSignalIn Signal that is "paired" with the sensor
       * @param index Index in the sensor array (Just for saving computing time)
       */
      StationSensor(int pin, int index)
      {
        this->pin = pin;
        this->state = true;
        // this->theSignal = theSignalIn;
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
        this->state = digitalRead(this->pin);
        return this->state;
      } 

      /**
       * @brief Get the direction the sensor is indicating for
       * 
       * @return Signal->signalDirection
       */
      Direction getDirection()
      {
          return direction;
          // return theSignal->signalDirection;
      }

      /**
       * @brief Update function to be called each iteration in the main loop
       * 
       */
      virtual void update()
      {
          delayMicroseconds(10);

          readState();
          delayMicroseconds(10);
          // if(state == 0)
          // {
          //     theSignal->changeState(0);
          // }
        //   else
        //   {
        //       theSignal->changeState(1);
        //   }
      }

      bool getState()
      {
        delayMicroseconds(10);
        // Serial.println(state);
        return state;
      }

};


class Sensor: public StationSensor
{
  public:
    Signal* theSignal = nullptr;

    Sensor(int pin, Signal* theSignalIn, int index): StationSensor(pin, index)
    {
      this->theSignal = theSignalIn;
      pinMode(this->pin, INPUT);
    }

    void update()
    {
      delayMicroseconds(10);

      readState();
      delayMicroseconds(10);
      if(state == 0)
      {
          theSignal->changeState(0);
      }
    }
};
/**
 * @brief Array of sensors
 * 
 */
Sensor sensorArray[2] =
{
    Sensor(IRL1, &signalArray[0], 0),
    Sensor(IRR1, &signalArray[1], 1),
    // Sensor(IRL2, &signalArray[2], 2),
    // Sensor(IRR2, &signalArray[3], 3)

};
