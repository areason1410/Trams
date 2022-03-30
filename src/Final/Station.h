#pragma once
#include "Sensor.h"


class Station
{
public:
    StationSensor *leftSensor = nullptr, *rightSensor = nullptr;
    Destination stationLocation;
    Section stationSection;
    bool isOccupied = false;
    bool trainCanLeave = true;

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
        if(isOccupied == false && trainDetected())
        {
            isOccupied = true;
            trainCanLeave = false;
        }
        
        if(trainCanLeave == true && isOccupied == true && trainDetected())
        {
            isOccupied = false;
        }
    }

private:
    bool trainDetected()
    {
        if(leftSensor->getState() == IRHIGH || rightSensor->getState() == IRHIGH)
            return true;

        else return false;
    }

};

Station stationArray[3] =
{
    Station(nullptr, &stationSensorArray[0], Salisbury),
    Station(&stationSensorArray[1], &stationSensorArray[2], Bemerton),
    Station(&stationSensorArray[3], nullptr, Wilton),
};
