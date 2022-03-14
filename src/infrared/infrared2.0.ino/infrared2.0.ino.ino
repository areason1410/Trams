  class Sensor {
    public:
      bool state;
      int pin;
      Signal theSignal;

      Sensor(int pin, Signal theSignal) {

        this->pin = pin;
        this->state = false;
        this->theSignal = theSignal
        pinMode(this->pin, INPUT);
      }
      void readState() {
        this->state = digitalRead(this->pin);
        return this->state;
      } 
  };
  enum Direction{
    Forward = 1, 
    Backward = -1
  }
  // class SensorGroup {
  //   public:
  //   Direction
  //   SensorGroup(Sensor s1, Sensor s2){
  //     this->sensors[0] = s1;
  //     this->sensors[1] = s2;
  //   }
    
  //   private:
  //   Sensor sensors[2];
  // };
  
void setup() {
 
}


 void loop(){
 }

