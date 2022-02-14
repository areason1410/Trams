#include "train.h"


Train train1(A, Wilton, 1);

void setup() 
{
    Serial.begin(9600);
    pinMode(IRR1, INPUT);
    pinMode(IRR2, INPUT);
    pinMode(IRL1, INPUT);
    pinMode(IRL2, INPUT);
    pinMode(LEDLR, OUTPUT);
    pinMode(LEDLG, OUTPUT);
    pinMode(LEDRR, OUTPUT);
    pinMode(LEDRG, OUTPUT);
    pinMode(motor1, OUTPUT);
    pinMode(motor1, OUTPUT);
    pinMode(speedPin, OUTPUT);

}
void loop()
{
    // MAKE SURE TO UPDATE SENSORS FIRST
    updateSensers();


    // MAKE SURE TO UPDATE TRAINS SECOND
    train1.update();
    //Serial.println(digitalRead(IRL2));


    // MAKE SURE TO UPDATE SIGNALS LAST
    updateSignals();
}
