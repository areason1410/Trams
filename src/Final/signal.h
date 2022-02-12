#pragma once

#include "occupancy.h"

const byte LEDLG = 5;
const byte LEDLR = 6;

const byte LEDRG = 7;
const byte LEDRR = 8;


byte LEDArray[4] = {LEDLG, LEDLR, LEDRG, LEDRR};


class Signal
{
public:

    bool m_isEmpty;
    Section m_nextSection;

    Signal(byte green, byte red, Section sect):
    m_greenPin(green), m_redPin(red), m_nextSection(sect)
    {
        m_isEmpty = true;
        setGreen();
    }

    /*
        Set LED's according to if the current section
        is empty and is the next section.
        by default m_isEmpty = true
    */
    void update()
    {
        for(MapData &data : Map)
        {
            if(digitalRead(data.pin) == 0 && data.newSection == m_nextSection)
            {
                setRed();
                m_isEmpty = false;
            }
            else
            {
                setGreen();
                m_isEmpty = true;
            }
        }
    }

    bool checkIfIsNextSection(Section currentSection)
    {
        return (int)m_nextSection == (int)currentSection+1;
    }

private:
    byte m_greenPin;
    byte m_redPin;

    // make signal green
    void setGreen()
    {
        digitalWrite(m_greenPin, HIGH);
        digitalWrite(m_redPin, LOW);
        m_isEmpty = true;
    }

    //make signal red
    void setRed()
    {
        digitalWrite(m_greenPin, LOW);
        digitalWrite(m_redPin, HIGH);
        m_isEmpty = false;
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
