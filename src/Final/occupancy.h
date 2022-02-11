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

Section section = A;
Destination destination = Wilton;
Section destinationSection = (Section)((int)destination+1);

/*
    Array which contains the IR Sensors pins in
    Salisbury -> Wilton Order
    As we are currently only working with 3 section
    and 2 IR Points we label them Left and Right
    Left is Wilton, Right is Salisbury
*/
byte IRArray[4] = {IRL1, IRL2, IRR1, IRR2};

// temporary value to calculate next section
byte tempValue = 0;


/*
    MapData for each IR senser and their respective destination
    Calculates the new section based on the destination and
    index in the IRArray
*/
struct MapData
{
  byte pin;
  Destination destination;
  Section newSection;

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

//Function to 
void setNextSection()
{
  /*
      Iterate over the IRArray to find which sensor is currently active
      then store that pin in the tempValue variable
  */
  for(byte &pin : IRArray)
  {
    if(digitalRead(pin) == 0)
    {
      tempValue = pin;
    }
  }

  /*
      Iterate over the map data and compare the tempValue to the
      map data, if the tempValue is the same as the pin for the 
      map data then set the current section equal to the calculated
      new section from the map data
  */
  for(MapData &data : Map)
  {
    if(tempValue == data.pin)
    {
      section = data.newSection;
    }
  }
}