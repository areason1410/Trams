byte IRR1 = 3;
byte IRR2 = 4;

byte IRL1 = 6;
byte IRL2 = 7;

byte LEDLR = 13;
byte LEDLG = 12;

byte LEDRR = 11;
byte LEDRG = 10;

//byte LIR = [IRL1, IRL2];
//byte RIR = [IRR1, IRR2];

enum Section 
{
  A,
  B,
  C
};

enum Destination
{
  Salisbury,
  Wilton
};

byte IRArray[4] = {IRL1, IRL2, IRR1, IRR2};
byte tempValue = 0;

Section section = C;
Destination destination = Salisbury;


class signal {
  public:
    bool red
    bool green
  
  void setSignal(bool state) {
  if state == true { //there is a train in the next section
    red = true
    green = false
  } else {
    red = false
    green = true
  }
}
}

signal signal1;
signal signal2;
signal signal3;
signal signal4;



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

  for(int i = 0; i < sizeof(IRArray)/sizeof(byte); i++)
  {
    if(digitalRead(IRArray[i]) == 0) 
    {
      tempValue = IRArray[i];
    }
  }

  if(tempValue == IRL1) 
  {
    if(destination == Salisbury) return;
    section = B;
  }
  else if(tempValue == IRL2)
  {
    if(destination == Wilton) return;
    section = A;
  }
  else if(tempValue == IRR1)
  {
    if(destination == Salisbury) return;
    section = C;
  }
  else if(tempValue == IRR2)
  {
    if(destination == Wilton) return;
    section = B;
  }
  
  Serial.println(section);



  if (Section == A) {
    signal1.setSignal(false)
    signal2.setSignal(true)
    signal3.setSignal(false)
    signal4.setSignal(false)
  } else if (Section == B) {
    signal1.setSignal(true)
    signal2.setSignal(false)
    signal3.setSignal(false)
    signal4.setSignal(true)
  } else if (Section == C) {
    signal1.setSignal(false)
    signal2.setSignal(false)
    signal3.setSignal(true)
    signal4.setSignal(false)
  } else {
    signal1.setSignal(false)
    signal2.setSignal(false)
    signal3.setSignal(false)
    signal4.setSignal(false)
  } 
}
