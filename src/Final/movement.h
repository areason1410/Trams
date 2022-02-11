#pragma once
#include "signal.h"

byte motor1 = 9;
byte motor2 = 10;
byte speedPin = 11;

void updateMovement()
{
    // if going to wilton, go forwards, else go back
    int8_t direction = destination == Wilton ? 1 : -1;

    if(section != destinationSection)
    {
        // 0 to 255
        analogWrite(speedPin, 100*direction);
    }
    else
    {
        analogWrite(speedPin, 0);
    }
}


