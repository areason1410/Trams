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
  Destination destination;
  Section newSection; // Section its detecting for

  MapData(byte pin, Destination destination):
  pin(pin), destination(destination)
  {
    for(int i = 0; i < sizeof(IRArray) / sizeof(byte); i++)
    {
      if(IRArray[i] == pin)
      {
        //newSection = i % 2 == 0 ? (Section)(i / 2) : (Section)((i+1) /2);
        if(destination == Wilton) 
        {
            newSection = (Section)((i / 2) + 1);
        }
        else if(destination == Salisbury)
        {
            newSection = (Section)(((i+1) / 2) - 1);
        }
      }
    }
  };


};

// Map Data for the track (IRSensors), order Wilton -> Salisbury
MapData Map[4] = 
{
  MapData(IRL1, Wilton),
  MapData(IRL2, Salisbury),
  MapData(IRR1, Wilton),
  MapData(IRR2, Salisbury),
};
