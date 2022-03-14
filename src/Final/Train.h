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

  Train(int leftMotorPin, int rightMotorPin, int speedPin, Direction trainDirection, Section startSection, Section endSection) 
  {
    this->leftMotorPin = leftMotorPin;
    this->rightMotorPin = rightMotorPin;
    this->speedPin = speedPin;
    this->trainDirection = trainDirection;
    this->currentSection = startSection;
    this->endSection = endSection;
    digitalWrite(leftMotorPin, HIGH);
    digitalWrite(rightMotorPin, LOW);
  }

  void changeDirection() 
  {
    
    if (digitalRead(leftMotorPin) == HIGH)
    {
      digitalWrite(leftMotorPin, LOW);
      digitalWrite(rightMotorPin, HIGH);
    }
    else if (digitalRead(leftMotorPin) == LOW);
    {
      digitalWrite(leftMotorPin, HIGH);
      digitalWrite(rightMotorPin, LOW);
    }
  }

  void start() 
  {
    digitalWrite(speedPin, 255);
  }

  void trainStop() 
  {
    digitalWrite(speedPin, 0);
  }

  void update()
  {
      if(currentSection == endSection) return;
      
      for(Sensor &sensor : sensorArray)
      {
          if(sensor.theSignal.section == (Section)((int)this->currentSection+1) && sensor.theSignal.getState() != 1)
          {
              trainStop();
          }
          else
          {
              start();
          }
      }

  }
 };