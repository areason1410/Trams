#include "Train.h"
Destination train1Stops[3] = {Salisbury, Bemerton, Wilton};
Train train1(motorLeftPin1, motorRightPin1, speedPin1, Forward, train1Stops, ARRSIZE(train1Stops));
void setup() 
{

    pinMode(SalisburyIRRight, INPUT);
    pinMode(BemertonIRRight, INPUT);
    pinMode(BemertonIRLeft, INPUT);
    pinMode(WiltonIRLeft, INPUT);
    pinMode(AIRRight, INPUT);
    pinMode(ALEDGreenBackward, OUTPUT);
    pinMode(ALEDGreenForward, OUTPUT);
    pinMode(ALEDRedBackward, OUTPUT);
    pinMode(ALEDRedForward, OUTPUT);
    pinMode(BIRLeft, INPUT);
    pinMode(BIRRight, INPUT);
    pinMode(BLEDRedForward, OUTPUT);
    pinMode(BLEDRedBackward, OUTPUT);
    pinMode(BLEDGreenBackward, OUTPUT);
    pinMode(BLEDGreenForward, OUTPUT);
    pinMode(CIRLeft, INPUT);
    pinMode(CLEDRedForward, OUTPUT);
    pinMode(CLEDRedBackward, OUTPUT);
    pinMode(CLEDGreenBackward, OUTPUT);
    pinMode(CLEDGreenForward, OUTPUT);
    pinMode(speedPin1, OUTPUT);
    pinMode(motorLeftPin1, OUTPUT);
    pinMode(motorRightPin1, OUTPUT);
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}


void loop() 
{
    digitalWrite(13, HIGH);
    for(Sensor &sensor: sensorArrayForward)
    {
        sensor.update();
    }

    for(Sensor &sensor: sensorArrayBackward)
    {
        sensor.update();
    }
    
    
    for(StationSensor &sensor: stationSensorArray)
    {
        sensor.update();
    }

    train1.update();
}
