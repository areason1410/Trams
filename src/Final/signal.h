#pragma once

#include "occupancy.h"

const byte LEDLG = 5;
const byte LEDLR = 6;

const byte LEDRG = 7;
const byte LEDRR = 8;


byte LEDArray[4] = {LEDLG, LEDLR, LEDRG, LEDRR};


struct Signal
{
    byte greenPin;
    byte redPin;
    bool isEmpty;
    Section nextSection;

    Signal(byte green, byte red, Section sect):
    greenPin(green), redPin(red), nextSection(sect)
    {
        isEmpty = true;
        update();
    }

    // helper function to check if it is the next section
    bool checkIfIsNextSection()
    {
        return (int)section == (int)nextSection-1;
    }

    // make signal green
    void setGreen()
    {
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, LOW);
        isEmpty = true;
    }

    //make signal red
    void setRed()
    {
        digitalWrite(greenPin, LOW);
        digitalWrite(redPin, HIGH);
        isEmpty = false;
    }

    /*
        Set LED's according to if the current section
        is empty and is the next section.
        by default isEmpty = true
    */
    void update()
    {
        if(checkIfIsNextSection() && isEmpty == true)
        {
            setGreen();
        }
        else
        {
            setRed();
        }
    }
};

Signal SignalArray[2] =
{
    Signal(LEDLG, LEDLR, B),
    Signal(LEDRG, LEDRR, C)
};



void updateSignals()
{
    for(Signal &signal : SignalArray)
    {
        signal.update();
    }
}


/*
    Checks if the next section is free.
    If it isn't returns false to tell the train
    to stop.
*/
bool nextSectionIsFree()
{
    for(Signal &signal : SignalArray)
    {
        if(signal.checkIfIsNextSection() && signal.isEmpty == true)
        {
            return true;
        }
    }

    return false;
}