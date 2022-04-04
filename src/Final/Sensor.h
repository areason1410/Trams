#pragma once
#include "Signal.h"

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
          this->state = digitalRead(this->pin);
      }

      bool getState()
      {
        // delay(1);
        return state;
      }

};


class Sensor: public StationSensor
{
  public:
    Signal* theSignal;
    Direction direction;

    Sensor(int pin, Signal* theSignalIn, int index, Direction direction): StationSensor(pin, index)
    {
      this->theSignal = theSignalIn;
      this->direction = direction;
    }

    void update()
    {
      readState();
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
Sensor sensorArrayForward[2] =
{
    Sensor(BIRLeft, &signalArray[0], 0, Forward),
    Sensor(CIRLeft, &signalArray[1], 1, Forward),

};

Sensor sensorArrayBackward[2] =
{
    Sensor(AIRRight, &signalArray[3], 0, Backward),
    Sensor(BIRRight, &signalArray[2], 1, Backward),

};

StationSensor stationSensorArray[4]
{
  StationSensor(SalisburyIRRight, 0),
  StationSensor(BemertonIRLeft, 1),
  StationSensor(BemertonIRRight, 2),
  StationSensor(WiltonIRLeft, 3),
};
