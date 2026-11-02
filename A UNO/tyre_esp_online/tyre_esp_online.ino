// === FINAL MOTOR CONTROL CODE (ALL DIRECTIONS CORRECT) ===
// Forward/Backward + Left/Right all fixed correctly now.

const int IN1 = 2;   // Left Motor
const int IN2 = 3;
const int ENA = 5;

const int IN3 = 4;   // Right Motor
const int IN4 = 7;
const int ENB = 6;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();
  Serial.println("✅ Motor Control Ready (All directions fixed)");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'F') forward(200);
    else if (cmd == 'B') backward(200);
    else if (cmd == 'L') leftTurn(200);
    else if (cmd == 'R') rightTurn(200);
    else if (cmd == 'S') stopMotors();

    Serial.print("Command: ");
    Serial.println(cmd);
  }
}

// === Movement Functions ===

// ✅ Forward
void forward(uint8_t speed) {
  // Both motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

// ✅ Backward
void backward(uint8_t speed) {
  // Both motors backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

// ✅ Left Turn (swapped correctly now)
void leftTurn(uint8_t speed) {
  // Left motor forward, right motor backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

// ✅ Right Turn (swapped correctly now)
void rightTurn(uint8_t speed) {
  // Left motor backward, right motor forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

// ✅ Stop
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("🛑 Motors stopped.");
}
