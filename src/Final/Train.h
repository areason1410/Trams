#pragma once
#include "Enums.h"
#include "Sensor.h"

byte motorLeft = 9;
byte motorRight = 10;
byte speedPin = 11;

class Train {
public:
  byte currentSpeed;
  byte maxSpeed;
  int leftMotorPin;
  int rightMotorPin;
  int speedPin;
  Direction trainDirection;
  Section currentSection;
  Section endSection;

  /**
   * @brief Construct a new Train object
   * 
   * @param leftMotorPin Pin for left motor
   * @param rightMotorPin Pin for right motor
   * @param speedPin Analog pin for speed
   * @param trainDirection Direction train is travelling in
   * @param startSection Where the train starts
   * @param destination Where the train ends
   */
  Train(int leftMotorPin, int rightMotorPin, int speedPin, Direction trainDirection, Destination startLocation, Destination destination)
  {
    this->leftMotorPin = leftMotorPin;
    this->rightMotorPin = rightMotorPin;
    this->speedPin = speedPin;
    this->trainDirection = trainDirection;
    this->currentSection = destinationSection(startLocation);
    this->endSection = destinationSection(destination);
    digitalWrite(leftMotorPin, HIGH);
    digitalWrite(rightMotorPin, LOW);

    if(destination == Wilton)
    {
      nextSensor = &sensorArray[0];
    }
    else
    {
      nextSensor = &sensorArray[1];
    }
    // nextSensor = &sensorArray[0];
    // for(Sensor &sensor : sensorArray)
    // {
    //   delayMicroseconds(10);
    //     Serial.println("LOLLY");

    //   if(sensor.theSignal->section == checkIfIsNextSection(currentSection, *sensor.theSignal))
    //   {
    //     Serial.println("LOL");
    //     // Serial.println(sensor.getState());
    //     nextSensor = &sensor;
    //     // Serial.println(nextSensor->getState());

    //   }
    // }
    start();
  }

  /**
   * @brief Change direction of the train
   * 
   */
  void changeDirection() 
  {
    
    if (trainDirection == Forward)
    {
      digitalWrite(leftMotorPin, LOW);
      digitalWrite(rightMotorPin, HIGH);
      trainDirection = Backward;
    }
    else;
    {
      digitalWrite(leftMotorPin, HIGH);
      digitalWrite(rightMotorPin, LOW);
      trainDirection = Forward;
    }
  }

  /**
   * @brief Start the train
   * 
   */
  void start() 
  {
    digitalWrite(speedPin, 255);
  }

  /**
   * @brief Stop the train
   * 
   */
  void trainStop() 
  {
    digitalWrite(speedPin, 0);
  }

  
  /**
   * @brief Update function to be called each iteration in the main loop
   * 
   */
  void update()
  {
    delayMicroseconds(1);

    
    if(currentSection == endSection)
    {
      Serial.println("Test");
      decelerate();
      if (currentSpeed < 1)
      {
        delay(5000);
        changeDirection();
        endSection = A; 
      }
      // endSection = A;
      // changeDirection();
      
      return;
    } 
    else
    {
      accelerate();
    }


    if(nextSectionIsFree() == false)
    {
      updateSection();
      return;
    }

    
    

  }

  private:
    Sensor* nextSensor = nullptr;

    /**
     * @brief Helper function to check if the next section is free
     * If it isn't the train will stop otherwise it will continue
     * 
     * @return bool
     */
    bool nextSectionIsFree()
    {
      delayMicroseconds(1);
      if(nextSensor->theSignal->getState() == 1)
      {
          return true;
      }
      
      return false;
    }

    /**
     * @brief Function to be called in update which will change the current
     * section if necassary
     * 
     */
    void updateSection()
    {
        delayMicroseconds(1);
      if(nextSensor->getState() == 1)
      {
        
      }
      else
      {
        currentSection = nextSensor->theSignal->section;

        nextSensor = &sensorArray[nextSensor->index+1];
      }
    }

    void accelerate() {
      if(currentSpeed < 255)
      {
        currentSpeed += 0.1;
        analogWrite(pin, (int)currentSpeed);
      }
      
//      if speed <= 0 
//      then accelerate = true
//      if (speed > 254)
//      {
//        accelerate = false
//      }

    }

    void decelerate() {
      if (currentSpeed > 0)
      {
        currentSpeed -= 0.1;
        analogWrite(pin, (int)currentSpeed);
      }

       

//       if (speed = 255)
//       {
//          accelerate = false
//          decelerate = true
//       }
//       analogWrite(pin, (int)currentSpeed)
//       }

    }

 };
