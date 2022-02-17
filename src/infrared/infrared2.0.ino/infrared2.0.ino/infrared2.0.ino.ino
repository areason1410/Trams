  int IRR1 = 1;
  int IRL1 = 2;
  int GL = 5;
  int RL = 6;

void setup() {
  pinMode(IRR1, INPUT);
  pinMode(IRL1, INPUT);
  pinMode(GL, OUTPUT);
  pinMode(RL, OUTPUT);
}

void loop() {
  class Sensor {
    public:
      byte IRR1;
      byte IRL2;
  };
  
  
  class sensorGroup {
    byte IRArray[2] = {IRR1, IRL1};
  };
  
  class mapData {
    byte pin;
    byte Direction;
    byte nextSection;
    bool sensorTriggered;
  }; 

}

  int sensorTriggered1 = digitalRead (IRR1);
  int sensorTriggered2 = digitalRead (IRR1);

  if (sensorTriggered1 == true) then{
    if (sensorTriggered2 == true)
    digitalWrite(GL, HIGH);
//    this shows as going forward
  };
  
  if (sensorTriggered2 == true) then{
    if (sensorTriggered1 == true)
    digitalWrite(RL, HIGH);
//    this shows train going backward

  };
 };
 

  
