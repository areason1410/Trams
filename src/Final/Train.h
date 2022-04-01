#pragma once
#include "Enums.h"
#include "Station.h"

byte motorLeft = 9;
byte motorRight = 10;
byte speedPin = 11;

struct StationStructure { 
   Station* destination; 
   struct StationStructure *previousStation; 
   struct StationStructure *nextStation; 
}; 

class Train {
public:
  byte currentSpeed;
  byte maxSpeed;
  int leftMotorPin;
  int rightMotorPin;
  int speedPin;

  Direction trainDirection;
  Section currentSection;
  Station* nextStation = nullptr;
  StationStructure* trainDestinations = NULL;
  Sensor* nextSensor = nullptr;




  /**
   * @brief Construct a new Train object (Overloaded)
   * 
   * @param leftMotorPin 
   * @param rightMotorPin 
   * @param speedPin 
   * @param trainDirection 
   * @param startLocation 
   * @param destinations 
   * @param destinationCount
   */
  Train(int leftMotorPin, int rightMotorPin, int speedPin, Direction trainDirection, Destination* destinations, int destinationCount)
  {
      // Serial.println("lol");
    this->leftMotorPin = leftMotorPin;
    this->rightMotorPin = rightMotorPin;
    this->speedPin = speedPin;
    this->trainDirection = trainDirection;
    this->currentSection = destinationSection(destinations[0]);

    for(int i = 0; i < destinationCount; i++)
    {
      addStop(&stationArray[(int)destinations[i]]);
    }


    if(trainDirection == Forward)
    {
      nextSensor = &sensorArrayForward[0];
    }
    else
    {
      // nextSensor = &sensorArrayForward[ARRSIZE(sensorArraFory)-2];
    }
    
    digitalWrite(leftMotorPin, HIGH);
    digitalWrite(rightMotorPin, LOW);

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
    else
    {
      digitalWrite(leftMotorPin, HIGH);
      digitalWrite(rightMotorPin, LOW);
      trainDirection = Forward;
    }
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
    delay(1);
    // analogWrite(speedPin, 255);
      accelerate();
    if(nextStation->stationSection == currentSection && nextStation->trainCanLeave == false)
    {
      decelerate();
      if(nextStation->isOccupied == true)
      {
        delay(1000);
        trainStop();
        delay(5000);
        nextStation->trainCanLeave = true;
        accelerate();
        updateStation();
      }
    }
    
    
    

    if(nextSectionIsFree() == false)
    {
      updateSection();
      return;
    }

  }

  private:

    /**
     * @brief Helper function to check if the next section is free
     * If it isn't the train will stop otherwise it will continue
     * 
     * @return bool
     */
    bool nextSectionIsFree()
    {
      // delay(1);
      if(nextSensor->theSignal->getState() == IRLOW)
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
      if(trainDirection == Forward)
      {
          if(nextSensor->index == ARRSIZE(sensorArrayForward)-1)
          {
            changeDirection();
            currentSection = nextSensor->theSignal->section;
            nextSensor = &sensorArrayBackward[1];

          }
          else
          {
            currentSection = nextSensor->theSignal->section;
            nextSensor = &sensorArrayForward[nextSensor->index+1];
          }
      }
      else
      {
        if(nextSensor->index == 0)
        {
          changeDirection();
          currentSection = nextSensor->theSignal->section;
          nextSensor = &sensorArrayForward[0];
        }
        // else
        // {
        //   currentSection = nextSensor->theSignal->section;
        //   nextSensor = &sensorArrayBackward[nextSensor->index-1];
        // }
      }
      // if(nextSensor->index+1 > ARRSIZE(sensorArray) || nextSensor->index != 0)
      // {
      //   changeDirection();
      //   return;
      // }
      // else
      // {
        // currentSection = nextSensor->theSignal->section;
        // nextSensor->theSignal->changeState(1);
        // nextSensor = &sensorArrayForward[nextSensor->index+1];
      // }
        // setNextSection();
      
    }

    void setNextSection()
    {
      // if(nextSensor->index+1 > ARRSIZE(sensorArray) || nextSensor->index == 0)
      // {
      //   changeDirection();
      //   return;
      // }
      // else
      // {
        currentSection = nextSensor->theSignal->section;
        nextSensor->theSignal->changeState(1);
        nextSensor = &sensorArrayForward[nextSensor->index+1];
      // }
    }

    void accelerate() 
    {
      if(currentSpeed < 255)
      {
        currentSpeed += 1;
        analogWrite(speedPin, (int)currentSpeed);
      }
    }

    void decelerate() 
    {
      if(currentSpeed > 0 )
      {
        currentSpeed -= 0.1;
        analogWrite(speedPin, (int)currentSpeed);
      }

    }


  void addStop(Station* stop) 
  { 
    StationStructure* newnode = new StationStructure; 
    StationStructure* last = trainDestinations;

    newnode->destination = stop;
    newnode->nextStation = NULL;

    if(trainDestinations == NULL)
    {
      trainDestinations = newnode;
      return;
    }
    
    while(last->nextStation != NULL)
    {
        last = last->nextStation;
        
    }

    newnode->previousStation = last;
    last->nextStation = newnode; 
    
  }   

  void updateStation()
  {
      StationStructure* ptr;
      ptr = trainDestinations;
      while(ptr != NULL)
      {
        if(ptr->destination == nextStation)
        {
          nextStation->trainCanLeave = false;
          if(trainDirection == Forward && !shouldChangeDirection())
          {
            nextStation = ptr->nextStation->destination;

          }
          else if(trainDirection == Backward && !shouldChangeDirection())
          {
            nextStation = ptr->previousStation->destination;
          }
          else
          {
            changeDirection();
            updateStation(); //cheeky recursion, i hope it doesnt kill us xd
          }
          ptr = NULL;
        }
        else
        {
          ptr = ptr->nextStation;
        }
      }
  }

  bool shouldChangeDirection()
  {
    if(trainDestinations->nextStation == NULL && trainDirection == Forward)
    {
      return true;
    }
    else if(trainDestinations->previousStation == NULL && trainDirection == Backward)
    {
      return true;
    }

    return false;
  }
 };





  // /**
  //  * @brief Construct a new Train object
  //  * 
  //  * @param leftMotorPin Pin for left motor
  //  * @param rightMotorPin Pin for right motor
  //  * @param speedPin Analog pin for speed
  //  * @param trainDirection Direction train is travelling in
  //  * @param startSection Where the train starts
  //  * @param destination Where the train ends
  //  */
  // Train(int leftMotorPin, int rightMotorPin, int speedPin, Direction trainDirection, Destination startLocation, Destination destination)
  // {
  //   this->leftMotorPin = leftMotorPin;
  //   this->rightMotorPin = rightMotorPin;
  //   this->speedPin = speedPin;
  //   this->trainDirection = trainDirection;
  //   this->currentSection = destinationSection(startLocation);
  //   this->endSection = destinationSection(destination);
  //   digitalWrite(leftMotorPin, HIGH);
  //   digitalWrite(rightMotorPin, LOW);

  //   if(destination == Wilton)
  //   {
  //     nextSensor = &sensorArray[0];
  //   }
  //   else
  //   {
  //     nextSensor = &sensorArray[1];
  //   }
  //   // nextSensor = &sensorArray[0];
  //   // for(Sensor &sensor : sensorArray)
  //   // {
  //   //   delay(10);
  //   //     Serial.println("LOLLY");

  //   //   if(sensor.theSignal->section == checkIfIsNextSection(currentSection, *sensor.theSignal))
  //   //   {
  //   //     Serial.println("LOL");
  //   //     // Serial.println(sensor.getState());
  //   //     nextSensor = &sensor;
  //   //     // Serial.println(nextSensor->getState());

  //   //   }
  //   // }
  // }