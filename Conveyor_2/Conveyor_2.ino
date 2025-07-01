#define in1 19
#define in2 18
#define enA 13

// ini untuk menyimpan inputan dari serial
String command = ""; 

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  Serial.begin(9600);
  Serial.println("masukan perintah: s, cw, acw");
}

void loop() {
  if (Serial.available() > 0) {
    // membaca input sampai newline
    command = Serial.readStringUntil('\n');

    // menghapus spasi diawal / akhir input
    command.trim();

    if (command == "s") {
      stopMotor();
    } else if (command == "cw") {
      clockWise();
    } else if (command == "acw") {
      antiClockWise();
    } else {
      Serial.println("perintah tidak dikenali");
      stopMotor();
    }

    Serial.println("masukan perintah lagi: s, cw, acw");
  }
}

// Fungsi berhenti
void stopMotor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  Serial.println("Motor berhenti");
  delay(5000);
}

// Putar searah jarum jam
void clockWise() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 65);
  Serial.println("Motor berputar searah jarum jam");
  delay(5000);
}

// Putar berlawanan arah jarum jam
void antiClockWise() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 65);
  Serial.println("Motor berputar berlawanan arah jarum jam");
  delay(5000);
}
