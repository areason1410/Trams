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


Section destinationSection(Destination destination)
{
    return (Section)((int)destination+1);
}