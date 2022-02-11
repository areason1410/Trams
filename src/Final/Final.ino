#include "occupancy.h"

const byte LEDLR = 13;
const byte LEDLG = 12;

const byte LEDRR = 11;
const byte LEDRG = 10;

Section section = A;
Destination destination = Wilton;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IRR1, INPUT);
  pinMode(IRR2, INPUT);
  pinMode(IRL1, INPUT);
  pinMode(IRL2, INPUT);
  pinMode(LEDLR, OUTPUT);
  pinMode(LEDLG, OUTPUT);
  pinMode(LEDRR, OUTPUT);
  pinMode(LEDRG, OUTPUT);

}
void loop() {
  // put your main code here, to run repeatedly:

  setNextSection(section);
  
  Serial.println(section);
}
