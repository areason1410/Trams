#include "Sensor.h"

class station {
    public:
    int section;
    signalF theSignalF;
    signalB theSignalB;


    station(int section, signalF theSignalF, signalB theSignalB) {

        this->section = section
        this->theSignalF = theSignalF
        this->theSignalB = theSignalF
    }
};
enum Destination {
    Salisbury
    BemertonHeath
    Wilton
};
    void location(Destination destination)
