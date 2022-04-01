#include "Train.h"
// #include "Station.h"
Destination train1Stops[3] = {Salisbury, Bemerton, Wilton};
Train train1(motorLeftPin1, motorRightPin1, speedPin1, Forward, train1Stops, ARRSIZE(train1Stops));
// Train* train1;
void setup() 
{

    pinMode(SalisburyIRRight, INPUT);
    pinMode(BemertonIRRight, INPUT);
    pinMode(BemertonIRLeft, INPUT);
    pinMode(WiltonIRLeft, INPUT);
    pinMode(AIRLeft, INPUT);
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
    pinMode(CIRRight, INPUT);
    pinMode(CLEDRedForward, OUTPUT);
    pinMode(CLEDRedBackward, OUTPUT);
    pinMode(CLEDGreenBackward, OUTPUT);
    pinMode(CLEDGreenForward, OUTPUT);
    pinMode(speedPin1, OUTPUT);
    pinMode(motorLeftPin1, OUTPUT);
    pinMode(motorRightPin1, OUTPUT);
    Serial.begin(9600);
    Serial.println(train1.currentSection);

    // if(train1 == nullptr)
    // train1 = new Train(motorLeftPin1, motorRightPin1, speedPin1, Forward, train1Stops, ARRSIZE(train1Stops));
}


void loop() 
{
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

//    for(Station &station: stationArray)
//    {
//        station.update();
//    }


    train1.update();
//    Serial.println(train1.currentSection);
//    Serial.println("---");
//    Serial.println((int)train1.trainDirection);
//    Serial.println(train1.nextSensor->theSignal->section);
    // Serial.println(digitalRead(BIRLeft));
}
