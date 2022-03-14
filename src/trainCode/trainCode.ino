void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

class Train {
  byte currentSpeed;
  byte maxSpeed;
  int leftMotorPin;
  int rightMotorPin;
  int speedPin;
  Direction trainDirection;

  Train(int leftMotorPin, int rightMotorPin, int speedPin, Direction trainDirection) {
    this->leftMotorPin = leftMotorPin;
    this->rightMotorPin = rightMotorPin;
    this->speedPin = speedPin;
    this->trainDirection = trainDirection;
      digitalWrite(leftMotorPin, HIGH);
      digitalWrite(rightMotorPin, LOW);
  }

  void changeDirection() {
    
    if (leftMotorPin = HIGH){
      digitalWrite(leftMotorPin = LOW)
      digitalWrite(rightMotorPin = HIGH) 
    }else if (leftMotorPin = LOW)
    {
      digitalWrite(leftMotorPin = HIGH)
      digitalWrite(rightMotorPin = LOW)
    }
  }

  void start() {
    digitalWrite(speedPin, 255)
  }

  void trainStop() {
    digitalWrite(speedPin, 0)
  }
 } 
