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
    Section nextSection;

    Signal(byte green, byte red, Section sect):
    greenPin(green), redPin(red), nextSection(sect)
    {
        update();
    }

    // make signal green
    void setGreen()
    {
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, LOW);
    }

    //make signal red
    void setRed()
    {
        digitalWrite(greenPin, LOW);
        digitalWrite(redPin, HIGH);
    }

    /*
        Set LED's according to if the current section
        is one behind the next one.
    */
    void update()
    {
        if((int)section == (int)nextSection-1)
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