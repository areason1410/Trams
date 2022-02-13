#pragma once


const byte IRR1 = 1;
const byte IRR2 = 2;

const byte IRL1 = 3;
const byte IRL2 = 4;

enum Section 
{
  A = 0,
  B,
  C
};

enum Destination
{
  Salisbury,
  Wilton
};

enum Direction
{
    Forward = 1,
    Backward = -1,
    None
};


/*
    Array which contains the IR Sensors pins in
    Salisbury -> Wilton Order
    As we are currently only working with 3 section
    and 2 IR Points we label them Left and Right
    Left is Wilton, Right is Salisbury
*/
byte IRArray[4] = {IRL1, IRL2, IRR1, IRR2};


/*
    MapData for each IR senser and their respective destination
    Calculates the new section based on the destination and
    index in the IRArray
*/
struct MapData
{
  byte pin;
  Direction direction;
  Section nextSection; // Section its detecting for
  bool sensorTriggered;

  MapData(byte pin, Direction direction):
  pin(pin), direction(direction)
  {
    sensorTriggered = false;
    for(int i = 0; i < sizeof(IRArray) / sizeof(byte); i++)
    {
      if(IRArray[i] == pin)
      {
        if(direction == Forward) 
        {
            nextSection = (Section)((i / 2) + 1);
        }
        else if(direction == Backward)
        {
            nextSection = (Section)(((i+1) / 2) - 1);
        }
      }
    }
  };

  void checkSensors()
  {
    if(digitalRead(pin) == 0)
    {
      sensorTriggered = true;
    }
    else
    {
      sensorTriggered = false;
    }
  }

};

// Map Data for the track (IRSensors), order Wilton -> Salisbury
MapData Map[4] = 
{
  MapData(IRL1, Forward),
  MapData(IRL2, Backward),
  MapData(IRR1, Forward),
  MapData(IRR2, Backward),
};

void updateSensers()
{
  for(MapData &data : Map)
  {
    data.checkSensors();
  }
}