#pragma once
#include "Sensor.h"


class Station
{
public:
    StationSensor *leftSensor = nullptr, *rightSensor = nullptr;
    Destination stationLocation;
    Section stationSection;
    Station(StationSensor* ls, StationSensor* rs, Destination location)
    {
        leftSensor = ls;
        rightSensor = rs;
        stationLocation = location;
        stationSection = destinationSection(location);
    }
    
    void update()
    {
        leftSensor->update();
        rightSensor->update();
    }

private:
    /* data */
};

Station stations[3] =
{
    Station(nullptr, &stationSensorArray[0], Salisbury),
    Station(&stationSensorArray[1], &stationSensorArray[2], Bemerton),
    Station(&stationSensorArray[3], nullptr, Wilton),
};
