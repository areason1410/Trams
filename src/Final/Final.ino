byte IRR1 = 3;
byte IRR2 = 4;

byte IRL1 = 6;
byte IRL2 = 7;

byte LEDLR = 13;
byte LEDLG = 12;

byte LEDRR = 11;
byte LEDRG = 10;



void setup() {
  // put your setup code here, to run once:
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
  
  if(digitalRead(IRR1) == 1) digitalWrite(LEDRG, HIGH);
  else digitalWrite(LEDRG, LOW);

}
