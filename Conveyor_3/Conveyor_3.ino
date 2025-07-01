#define in1 19
#define in2 18
#define enA 13

const int buttonCw  = 4;
const int buttonAcw = 16;
const int buttonStp = 17;

// Variabel tombol
int button1 = HIGH;
int button2 = HIGH;
int button3 = HIGH;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  // Pakai INPUT_PULLUP agar tidak perlu resistor eksternal
  pinMode(buttonCw, INPUT_PULLUP);
  pinMode(buttonAcw, INPUT_PULLUP);
  pinMode(buttonStp, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // Baca tombol
  button1 = digitalRead(buttonCw);
  button2 = digitalRead(buttonAcw);
  button3 = digitalRead(buttonStp);

  if (button1 == LOW) {
    clockWise();       // Panggil fungsi CW
  } else if (button2 == LOW) {
    antiClockWise();   // Panggil fungsi ACW
  } else if (button3 == LOW) {
    stopMotor();       // Panggil fungsi STOP
  }
}

// Fungsi berhenti
void stopMotor() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  Serial.println("Motor berhenti");
  delay(500); // debounce
}

// Putar searah jarum jam
void clockWise() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 65);
  Serial.println("Motor searah jarum jam");
  delay(500); // debounce
}

// Putar berlawanan arah jarum jam
void antiClockWise() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 65);
  Serial.println("Motor berlawanan arah jarum jam");
  delay(500); // debounce
}
