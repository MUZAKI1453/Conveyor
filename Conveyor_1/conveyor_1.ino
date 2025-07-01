#define in1 19
#define in2 18
#define enA 13

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
}

void loop() {
  // Rotate motor clockwise
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 100); // Set speed (0-255)
  delay(3000); // Rotate for 3 seconds

  // Stop motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  delay(1000); // Wait 1 second

  // Rotate motor anticlockwise
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 100); // Set speed
  delay(3000); // Rotate for 3 seconds

  // Stop motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  delay(1000); // Wait 1 second
}
