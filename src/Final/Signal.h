#pragma once
#include "Enums.h"

const byte LEDLG = 5;
const byte LEDLR = 6;

const byte LEDRG = 7;
const byte LEDRR = 8;

class Signal 
{
  public:
    int redPin;
    int greenPin; 
    bool state; // 1 = green 0 = red
    Direction signalDirection;
    Section section;
  
    Signal(int redPin, int greenPin, Direction signalDirection, Section section) 
    {
      this->redPin = redPin;
      this->greenPin = greenPin;
      this->signalDirection = signalDirection;
      this->section = section;
      this->state = 1;
      digitalWrite(greenPin, HIGH);
    }
    
    void changeState(bool type)
    {
      state = type;

      if (state == 1) 
      {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
      } else if (state == 0);
      {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
      }
    }

    bool getState()
    {
      return state;
    }
  
};


Signal signalArray[2] = 
{
    Signal(LEDLG, LEDLR, Forward, B),
    Signal(LEDRG, LEDRR, Forward, C)

};

bool checkIfIsNextSection(Section currentSection, Signal signalToCompare)
{
    return (int)signalToCompare.section == (int)currentSection+1*(int)signalToCompare.signalDirection;
}

