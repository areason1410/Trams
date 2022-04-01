#pragma once
#include "Enums.h"

class Signal 
{
  public:
    int redPin;
    int greenPin; 
    bool state; // 1 = green 0 = red
    Direction signalDirection;
    Section section;

    /**
     * @brief Construct a new Signal object
     * 
     * @param redPin Pin for red LED
     * @param greenPin Pin for green LED
     * @param signalDirection Direction of the signal
     * @param section The section the signal is indicating for
     */
    Signal(int greenPin, int redPin, Direction signalDirection, Section section) 
    {
      // delay(1);
      this->redPin = redPin;
      this->greenPin = greenPin;
      this->signalDirection = signalDirection;
      this->section = section;
      this->state = 1;
      digitalWrite(greenPin, HIGH);
      // Serial.println("xsfiasdjf");
    }
    
    /**
     * @brief Changes the signal to be red or green
     * 
     * @param type 1 = green 0 = Red
     */
    void changeState(bool type)
    {
      state = type;

      if (state == 1) 
      {
        delay(1);
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
      } 
      else
      {
        // Serial.println(state);
        delay(1);
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
      }
    }

    /**
     * @brief Get the state of the signal
     * 
     * @return state
     */
    bool getState()
    {
      return state;
    }
  
};

/**
 * @brief Array of all our signals
 * 
 */
Signal signalArray[4] = 
{
    Signal(BLEDGreenForward, BLEDRedForward, Forward, B),
    Signal(CLEDGreenForward, CLEDRedForward, Forward, C),
    Signal(BLEDGreenBackward, BLEDGreenBackward, Backward, B),
    Signal(ALEDGreenBackward, ALEDRedBackward, Backward, A),


};

/**
 * @brief Helper function to check for which signal is next
 * 
 * @param currentSection Current section of the train
 * @param signalToCompare Signal to compare
 * @return bool
 */
bool checkIfIsNextSection(Section currentSection, Signal signalToCompare)
{
  delay(1);
  return (int)signalToCompare.section == (int)currentSection+1*(int)signalToCompare.signalDirection;
}

