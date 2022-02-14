  int IRR1 = 1;
  int IRR2 = 2;
  int IRL1 = 3;
  int IRL2 = 4;
  int GL = 5;
  int RL = 6;

void setup() {
  pinMode(IRR1, INPUT);
  pinMode(IRR2, INPUT);
  pinMode(IRL1, INPUT);
  pinMode(IRL2, INPUT);
  pinMode(GL, OUTPUT);
  pinMode(RL, OUTPUT);
  
}

void loop() {
  int ss1 = digitalRead (IRR1);
  int ss2 = digitalRead (IRL1);
  int ss3 = digitalRead (IRR2);
  int ss4 = digitalRead (IRL2);

  if (ss1 + ss2 == 2){
    digitalWrite(GL, HIGH);
  }
  else {
    digitalWrite(RL, HIGH);
  }

  if (ss3 + ss4 == 2){
    digitalWrite(GL, HIGH);
  }
  else {
    digitalWrite(RL, HIGH);
  }
}
