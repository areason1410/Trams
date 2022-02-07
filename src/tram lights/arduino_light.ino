int LED = 12;
int LED2 = 4;
void setup() {
  pinMode(LED, OUTPUT); // Declare the LED as an output
  pinMode(LED2, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH); // Turn the LED on
  digitalWrite(LED2, HIGH);
}
