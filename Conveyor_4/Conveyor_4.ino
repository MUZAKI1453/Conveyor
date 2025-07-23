#include <ESP32Servo.h>
#define in1 19
#define in2 18
#define enA 13

Servo servo;
String command = "";

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  servo.attach(12);
  servo.write(90);

  Serial.begin(9600);
  Serial.println("Siap menerima perintah");
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "s") {
      stopMotor();
    } else if (command == "cw") {
      conveyorCW();
    } else if (command == "acw") {
      conveyorACW();
    } else if (command == "sv") {
      sortir();
    } else if (command == "ss") {
      stopMotor();
      sortir();
    } else {
      Serial.println("Perintah tidak dikenali");
      stopMotor();
    }
  }
}

// Fungsi dasar
void stopMotor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  Serial.println("Motor STOP");
}

void conveyorCW() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 70);  // sesuaikan kecepatan
  Serial.println("Motor CW");
}

void conveyorACW() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 70);
  Serial.println("Motor ACW");
}

void sortir() {
  Serial.println("Sortir: Servo aktif");
  servo.write(180);
  delay(500);  // hanya 0.5 detik agar cepat
  servo.write(90);
  Serial.println("Sortir: Selesai");
}
