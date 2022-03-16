#pragma once
#include "Enums.h"
#include "Sensor.h"

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
  Train(int leftMotorPin, int rightMotorPin, int speedPin, Direction trainDirection, Section startSection, Destination destination)
  {
    this->leftMotorPin = leftMotorPin;
    this->rightMotorPin = rightMotorPin;
    this->speedPin = speedPin;
    this->trainDirection = trainDirection;
    this->currentSection = startSection;
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
    
    if (digitalRead(leftMotorPin) == HIGH)
    {
      digitalWrite(leftMotorPin, LOW);
      digitalWrite(rightMotorPin, HIGH);
      trainDirection = Backward;
    }
    else if (digitalRead(leftMotorPin) == LOW);
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
    
    if(currentSection == endSection)
    {
      trainStop();
      return;
    } 

    if(nextSectionIsFree() == true)
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
      if(nextSensor->theSignal->state == 1)
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
      if(nextSensor->state == 1 && nextSensor->index < sizeof(sensorArray)/sizeof(Sensor))
      {
        currentSection = nextSensor->theSignal->section;
        nextSensor = &sensorArray[nextSensor->index+1];
      }
    }

 };