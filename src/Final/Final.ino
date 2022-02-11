#include "movement.h"

void setup() {

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
void loop() {

    setNextSection();
    updateSignals();
    updateMovement();

}
