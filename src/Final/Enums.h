#pragma once

enum Section 
{
  A,
  B,
  C
};

enum Direction 
{
  Forward = 1,
  Backward = -1
};

enum Destination
{
  Salisbury,
  Wilton
};

Section destinationSection(Destination destination)
{
    return (Section)((int)destination+1);
}

