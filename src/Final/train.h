#pragma once
#include "signal.h"

byte motor1 = 9;
byte motor2 = 10;
byte speedPin = 11;


// if going to wilton, go forwards, else go back


class Train
{
public:
    Section m_section;
    Destination m_destination;
    Section m_destinationSection;
    Direction m_direction;
    byte m_ID;

    Train(Section section, Destination destination, byte ID):
    m_section(section), m_destination(destination), m_ID(ID)
    {
        m_destinationSection = (Section)((int)m_destination+1);
        m_direction = m_destination == Wilton ? Forward : Backward;
    }

    void update()
    {

        //stop if the next section is not free / red light
        if(!nextSectionIsFree()) analogWrite(speedPin, 0);

        if(m_section != m_destinationSection)
        {
            // 0 to 255
            analogWrite(speedPin, 100);
            setMotorPins();
            setNextSection();
        }
        else
        {
            analogWrite(speedPin, 0);
        }
    }

private:

    /*
        Checks if the next section is free.
        If it isn't returns false to tell the train
        to stop.
    */
    bool nextSectionIsFree()
    {
        for(Signal &signal : SignalArray)
        {
            if(signal.checkIfIsNextSection(m_section) && signal.m_isEmpty)
            {
                return true;
            }
        }

        return false;
    }

    /*
        Function to update the current section.
        provided the sensor is active and is the 
        correct sensor
        
        Call this function after checking the next 
        section is free
    */
    void setNextSection()
    {
        for(MapData &data : Map)
        {
            if(data.sensorTriggered && (int)data.nextSection == (int)m_section+1)
            {
                m_section = data.nextSection;
            }
        }
    }

    /*
        Function to set the direction of the motor
        using the direction
        anything else means stop
    */
    void setMotorPins()
    {
        if(m_direction == Forward)
        {
            digitalWrite(motor1, HIGH);
            digitalWrite(motor2, LOW);
        }
        else if(m_direction == Backward)
        {
            digitalWrite(motor1, LOW);
            digitalWrite(motor2, HIGH);
        }
        else
        {
            digitalWrite(motor1, LOW);
            digitalWrite(motor2, LOW);
        }
    }
    


};


