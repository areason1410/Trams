#pragma once
#include "signal.h"

byte motor2 = 9;
byte motor1 = 10;
byte speedPin = 11;




// if going to wilton, go forwards, else go back


// class Train
// {
// public:
//     Section m_section;
//     Destination m_destination;
//     Section m_destinationSection;
//     Direction m_direction;
//     byte m_ID;
//     byte currentSpeed = 0;

//     Train(Section section, Destination destination, byte ID):
//     m_section(section), m_destination(destination), m_ID(ID)
//     {
//         m_destinationSection = destinationSection(m_destination);
//         m_direction = m_destination == Wilton ? Forward : Backward;
//     }

//     void update()
//     {

//         //stop if the next section is not free / red light
//         if(!nextSectionIsFree())
//         {
//             analogWrite(speedPin, 0) ;
//             return;
//         } 


//         if(m_section != m_destinationSection)
//         {
//             // 0 to 255
//             analogWrite(speedPin, 255);
//             setMotorPins();
//             setNextSection();
//         }
//         else
//         {
//             //currentSpeed -= 1;
//             analogWrite(speedPin, 0);
//         }
//     }

// private:

//     /*
//         Checks if the next section is free.
//         If it isn't returns false to tell the train
//         to stop.
//     */
//     bool nextSectionIsFree()
//     {
//         for(Signal &signal : SignalArray)
//         {
//             if(signal.checkIfIsNextSection(m_section) && signal.m_isEmpty)
//             {
//                 return true;
//             }
//         }

//         return false;
//     }

//     /*
//         Function to update the current section.
//         provided the sensor is active and is the 
//         correct sensor
        
//         Call this function after checking the next 
//         section is free
//     */
//     void setNextSection()
//     {
//         for(MapData &data : Map)
//         {
//             if(data.sensorTriggered && (int)data.nextSection == (int)m_section+1)
//             {
//                 m_section = data.nextSection;
//             }
//         }
//     }

//     /*
//         Function to set the direction of the motor
//         using the direction
//         anything else means stop
//     */
//     void setMotorPins()
//     {
//         if(m_direction == Forward)
//         {
//             digitalWrite(motor1, HIGH);
//             digitalWrite(motor2, LOW);
//         }
//         else if(m_direction == Backward)
//         {
//             digitalWrite(motor1, LOW);
//             digitalWrite(motor2, HIGH);
//         }
//         else
//         {
//             digitalWrite(motor1, LOW);
//             digitalWrite(motor2, LOW);
//         }
//     }
    


// };

class Train
{
public:
    
    Train(byte motorL, byte motorR, byte speedPin,
    Direction direction, float acceleration, float decleleration):
    m_motorL(motorL), m_motorR(motorR), m_speedPin(speedPin),
    m_direction(direction), m_accelerationSpeed(acceleration), m_decelerationSpeed(decleleration)
    {
        m_speed = 0;
        m_maxSpeed = 255;
        m_shouldDecelerate = false;
    }

    void start()
    {
        digitalWrite(m_motorL, HIGH);
        digitalWrite(m_motorR, LOW);
    };

    void stop()
    {
        //m_speed = abs(m_speed) >= 0 ? m_speed + 1 * m_deceleration : m_speed;
        digitalWrite(m_motorL, HIGH);
        digitalWrite(m_motorR, LOW);
        m_shouldDecelerate = true;
    }

    void reverse()
    {
        digitalWrite(m_motorL, LOW);
        digitalWrite(m_motorR, HIGH);
    }

    void update()
    {

        if(m_shouldDecelerate)
        {
            m_speed =  m_speed >= 0 ? m_speed - 1 * m_decelerationSpeed : m_speed;
            analogWrite(m_speedPin, (int)m_speed);

        }
        else
        {
            m_speed = m_speed <= m_maxSpeed ? m_speed + 1 * m_accelerationSpeed : m_speed;
            analogWrite(m_speedPin, (int)m_speed);

        }

    }
    
private:
    float m_speed, m_accelerationSpeed, m_decelerationSpeed;
    byte m_motorL, m_motorR, m_speedPin;
    Direction m_direction;
    int m_maxSpeed;
    bool m_shouldDecelerate;
};
