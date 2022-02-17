#include <Servo.h>

Servo myservo;  

int pos = 0;    


class Points {
  private:
  bool pointDirection;



  public:
  Points()
  {
    pointDirection = 0;
  }
  
  void changeDirection (bool pointDirection) {
    if (pointDirection == 0) {
      myservo.write(0);
    }
    else {
      myservo.write(15);
    }
  }
};


Points point1;


void setup() {
  myservo.attach(9);  
}

void loop() {
    point1.changeDirection(1);                   
}
