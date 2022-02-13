#pragma once

#include "occupancy.h"

const byte LEDLG = 5;
const byte LEDLR = 6;

const byte LEDRG = 7;
const byte LEDRR = 8;


class Signal
{
public:

    bool m_isEmpty;
    Section m_nextSection;
    Direction m_direction;

    Signal(byte greenPin, byte redPin, Direction direction, Section nextSection):
    m_greenPin(greenPin), m_redPin(redPin), m_direction(direction),
    m_nextSection(nextSection)
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
            if(data.sensorTriggered && data.nextSection == m_nextSection)
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
        return (int)m_nextSection == (int)currentSection+1*(int)m_direction;
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

// Our array of signals
Signal SignalArray[2] =
{
    Signal(LEDLG, LEDLR, Forward, B),
    Signal(LEDRG, LEDRR, Backward, C)
};

// Update each signal
void updateSignals()
{
    for(Signal &signal : SignalArray)
    {
        signal.update();
    }
}
