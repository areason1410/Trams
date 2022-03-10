  class Sensor {
    public:
      bool state;
      int pin;

      Sensor(int pin) {
        this->pin = pin;
        this->state = false;
        pinMode(this->pin, INPUT);
      }
      void readState() {
        this->state = digitalRead(this->pin);
      } 
  };
  enum Direction{
    Forward = 1, 
    Backward = -1
  }
  class SensorGroup {
    public:
    Direction
    SensorGroup(Sensor s1, Sensor s2){
      this->sensors[0] = s1;
      this->sensors[1] = s2;
    }
    
    private:
    Sensor sensors[2];
  };
  
void setup() {
 
}


 void loop(){
 }
