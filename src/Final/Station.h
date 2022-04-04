#pragma once
#include "Sensor.h"


class Station
{
public:
    StationSensor *leftSensor = nullptr, *rightSensor = nullptr;
    Destination stationLocation;
    Section stationSection;
    bool isOccupied;
    bool trainCanLeave;

    Station(StationSensor* ls, StationSensor* rs, Destination location)
    {
        leftSensor = ls;
        rightSensor = rs;
        stationLocation = location;
        stationSection = destinationSection(location);
        isOccupied = false;
        trainCanLeave = false;
    }
    
    void update()
    {
        if(leftSensor != nullptr) leftSensor->update();
        if(rightSensor != nullptr) rightSensor->update();
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
    
    bool isOccupiedBool()
    {
      return isOccupied;
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
