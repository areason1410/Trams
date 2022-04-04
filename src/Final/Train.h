#pragma once
#include "Enums.h"
#include "Station.h"

byte motorLeft = 9;
byte motorRight = 10;
byte speedPin = 11;

struct StationStructure { 
   Station* destination; 
   StationStructure *previousStation; 
   StationStructure *nextStation; 
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
  Station* nextStation;
  StationStructure* trainDestinations = NULL;
  Sensor* nextSensor = nullptr;

  bool changingDirection = false;




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
    nextStation = trainDestinations->nextStation->destination;
      // addStop(&stationArray[(int)destinations[0]]);
      // addStop(&stationArray[(int)destinations[1]]);
      // addStop(&stationArray[(int)destinations[2]]);



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

   // pass train as parameter to the station cuz the isoccupied isnt getting passed correctly
  void update()
  {
    delay(1);
          stationArray[0].update();
          stationArray[1].update();
          stationArray[2].update();
      accelerate();analogWrite(speedPin, 255);
    if(nextStation->trainCanLeave == false);
    {
      if(nextStation->isOccupied == true)
      {
        delay(250);
        trainStop();
        delay(2000);
        nextStation->trainCanLeave = true;
        analogWrite(speedPin, 255);
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
      delay(100);
      
      if(trainDirection == Forward)
      {
            Serial.println("xd");
            currentSection = nextSensor->theSignal->section;
            if(nextSensor->index < ARRSIZE(sensorArrayForward)-1)nextSensor = &sensorArrayForward[nextSensor->index+1];
      }
      else if(trainDirection == Backward)
      {
        // Serial.println("lol");
      
          {
            Serial.println("xdasdf");

            currentSection = nextSensor->theSignal->section;
            nextSensor = &sensorArrayBackward[1];
          }
      }

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

          if(trainDirection == Forward && !shouldChangeDirection())
          {
            nextStation->isOccupied = false;
            nextStation = ptr->nextStation->destination;
            nextStation->isOccupied = false;

            Serial.println("Updated");
          }
          else if(trainDirection == Backward && !shouldChangeDirection())
          {
            nextStation->isOccupied = false;

            nextStation = ptr->previousStation->destination;
            nextStation->isOccupied = false;

            Serial.print("Next Station: ");
            Serial.println((int)nextStation->stationLocation);
            delay(200);
          }
          else if(shouldChangeDirection())
          {
            Serial.println("GOING BACK");
            changeDirection();
            changingDirection = true;
            // updateSection();
            updateStation(); //cheeky recursion, i hope it doesnt kill us xd
            //delay(5000);
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

    if(trainDirection == Forward && nextStation->stationLocation == Wilton && nextStation->isOccupied == true)
    {
      return true;
    }
    else if(trainDirection == Backward && nextStation->stationLocation == Salisbury && nextStation->isOccupied == true)
    {
      return true;
    }

    return false;
  }
 };





