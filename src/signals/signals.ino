enum Direction
{
  Forward,
  Backward
};

class Signal 
{
  public:
    int redPin;
    int greenPin; 
    bool state; // 1 = green 0 = red
    Direction signalDirection;
  
  Signal(int redPin, int greenPin, Direction signalDirection) 
  {
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->signalDirection = signalDirection;
    state = 1;
    digitalWrite(greenPin, HIGH)
  }
  
  void changeState()
  {
    state = 1 - state

    if (state == 1) 
    {
      digitalWrite(redPin, HIGH)
      digitalWrite(greenPin, LOW) 
    } else if (state == 0)
    {
      digitalWrite(redPin, HIGH)
      digitalWrite(greenPin, LOW)
    }
  }

  bool getState(state)
  {
    return state
  }
  
};

void setup() 
{
  // put your setup code here, to run once:

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
