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
        // Serial.println("XD");

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
          // delay(1);

          // readState();
          // Serial.println("asdf");
            this->state = digitalRead(this->pin);
          // delay(1);
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
      // Serial.println("oasdg");
      this->theSignal = theSignalIn;
      this->direction = direction;
      // delay(100);
      // pinMode(this->pin, INPUT);
    }

    void update()
    {
      // delay(1);

      readState();
      // delay(1);
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




// Sensor s1(BIRLeft, &signalArray[0], 0, Forward);
// Sensor s2(BIRRight, &signalArray[1], 1, Backward);
// Sensor s3(AIRRight, &signalArray[2], 2, Backward);
// Sensor s4(CIRLeft, &signalArray[3], 3, Forward);

/**
 * @brief Array of sensors
 * 
 */
Sensor sensorArrayForward[2] =
{
    // s1,s2,s3,s4
    Sensor(BIRLeft, &signalArray[0], 0, Forward),
    Sensor(CIRLeft, &signalArray[1], 1, Forward),

};

Sensor sensorArrayBackward[2] =
{
    // s1,s2,s3,s4
    Sensor(AIRRight, &signalArray[3], 2, Backward),
    Sensor(BIRRight, &signalArray[2], 3, Backward),

};

StationSensor stationSensorArray[4]
{
  StationSensor(SalisburyIRRight, 0),
  StationSensor(BemertonIRLeft, 1),
  StationSensor(BemertonIRRight, 2),
  StationSensor(WiltonIRLeft, 3),
};
