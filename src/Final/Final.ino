#include "Train.h"

Train train1(9, 10, 11, Forward, A, Wilton);


void setup() 
{
    pinMode(IRR1, INPUT);
    pinMode(IRR2, INPUT);
    pinMode(IRL1, INPUT);
    pinMode(IRL2, INPUT);
    pinMode(LEDLR, OUTPUT);
    pinMode(LEDLG, OUTPUT);
    pinMode(LEDRR, OUTPUT);
    pinMode(LEDRG, OUTPUT);
    pinMode(motorLeft, OUTPUT);
    pinMode(motorRight, OUTPUT);
    pinMode(speedPin, OUTPUT);
    Serial.begin(9600);
}

void loop() 
{
    for(Sensor &sensor: sensorArray)
    {
        sensor.update();
    }

    train1.update();
}
