#pragma once


/**
 * @brief Enum for the sections on the track
 * 
 */
enum Section 
{
  A,
  B,
  C
};

/**
 * @brief Direction to help with automating
 * 
 */
enum Direction 
{
  Forward = 1,
  Backward = -1
};

/**
 * @brief Destination possibilites for the train
 * 
 */
enum Destination
{
  Salisbury,
  Wilton
};

/**
 * @brief Helper function that returns the section of a given destination
 * 
 * @param destination 
 * @return The section for a given destination
 */
Section destinationSection(Destination destination)
{
    return (Section)((int)destination+1);
}

