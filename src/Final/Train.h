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
    for(Sensor &sensor : sensorArray)
    {
      if(sensor.theSignal->section == checkIfIsNextSection(currentSection, *sensor.theSignal))
      {
        nextSensor = &sensor;
      }
    }
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
    // Serial.println("Test12");
    delayMicroseconds(1);

    // Serial.println((int)currentSection);
    // Serial.println((int)endSection);
        // Serial.println((int)currentSection);
    
    if(currentSection == endSection)
    {
      Serial.println("Test");
      trainStop();
      // endSection = A;
      // changeDirection();
      return;
    } 
    // Serial.println("A");
    // Serial.println(nextSensor->state);
    // Serial.println("A");

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
          // Serial.println("asdf");
          return true;
      }
      // Serial.println("asdf1231");
      
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
        Serial.println(nextSensor->state);
      if(nextSensor->state == 1)
      {
        // Serial.println("testtyy");
        
      }
      else
      {
        // Serial.println("test");

        // for(int i = 0; i < 100; i++)
        // {
        // Serial.println("lmfaoo");

        // }
        currentSection = nextSensor->theSignal->section;

        nextSensor = &sensorArray[nextSensor->index+1];
      }
    }

 };