#include "Train.h"

Train* train1;

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
    Destination train1Stops[3] = {Salisbury, Bemerton, Wilton};
    train1 = new Train(9, 10, 11, Forward, train1Stops, ARRSIZE(train1Stops));
}


void loop() 
{
    for(Sensor &sensor: sensorArray)
    {
        sensor.update();
    }
    
    for(StationSensor &sensor: stationSensorArray)
    {
        sensor.update();
    }

    for(Station &station: stationArray)
    {
        station.update();
    }

    train1->update();
}
