#include "Train.h"

Train* train1;

void setup() 
{


    /**
     * @brief DO THE PINMODES BEFORE U TEST U DINGUS
     * 
     */
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
