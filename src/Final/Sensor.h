#pragma once
#include "Signal.h"


const byte IRL1 = 2;
const byte IRL2 = 12;
const byte IRR1 = 3;
const byte IRR2 = 4;

byte IRArray[4] = {IRL1, IRL2, IRR1, IRR2};

#define IRHIGH 0
#define IRLOW 1

class StationSensor
{
    public:
      bool state;
      int pin;
      int index;

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
        this->state = IRLOW;
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
       * @brief Update function to be called each iteration in the main loop
       * 
       */
      virtual void update()
      {
          delay(10);

          readState();
          delay(10);
      }

      bool getState()
      {
        delay(10);
        return state;
      }

};


class Sensor: public StationSensor
{
  public:
    Signal* theSignal = nullptr;
    Direction direction;

    Sensor(int pin, Signal* theSignalIn, int index, Direction direction): StationSensor(pin, index)
    {
      this->theSignal = theSignalIn;
      this->direction = direction;
      pinMode(this->pin, INPUT);
    }

    void update()
    {
      delay(10);

      readState();
      delay(10);
      if(state == IRHIGH)
      {
          theSignal->changeState(0);
      }
    }

      /**
       * @brief Get the direction the sensor is indicating for
       * 
       * @return direction
      */
      Direction getDirection()
      {
          return direction;
      }
};


/**
 * @brief Array of sensors
 * 
 */
Sensor sensorArray[6] =
{
    Sensor(AIRLeft, &signalArray[0], 0, Forward),
    Sensor(AIRRight, &signalArray[1], 1, Backward),
    Sensor(BIRLeft, &signalArray[2], 2, Forward),
    Sensor(BIRRight, &signalArray[3], 3, Backward),
    Sensor(CIRLeft, &signalArray[4], 4, Forward),
    Sensor(CIRRight, &signalArray[5], 5, Backward),

};

StationSensor stationSensorArray[4]
{
  StationSensor(SalisburyIRRight, 0),
  StationSensor(BemertonIRLeft, 1),
  StationSensor(BemertonIRRight, 2),
  StationSensor(WiltonIRLeft, 3),
};
