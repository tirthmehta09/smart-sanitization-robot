// === Final Fixed L293D Dual Motor Control (Arduino UNO) ===
// Forward/backward swapped as per your setup

const int IN1 = 2;   // Motor A (Left)
const int IN2 = 3;
const int ENA = 5;   // PWM pin

const int IN3 = 4;   // Motor B (Right)
const int IN4 = 7;
const int ENB = 6;   // PWM pin

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();
  Serial.println("✅ Motor control setup ready (Forward/Backward swapped).");
  delay(1000);
}

void loop() {
  Serial.println("⬆️ Forward");
  forward(200);
  delay(2000);

  Serial.println("🛑 Stop");
  stopMotors();
  delay(1000);

  Serial.println("⬇️ Backward");
  backward(200);
  delay(2000);

  Serial.println("🛑 Stop");
  stopMotors();
  delay(1000);

  Serial.println("➡️ Right Turn");
  rightTurn(200);
  delay(1500);

  Serial.println("⬅️ Left Turn");
  leftTurn(200);
  delay(1500);

  Serial.println("🛑 Stop");
  stopMotors();
  delay(2000);
}

// === Movement functions ===

// ✅ Swapped logic: Forward = earlier backward direction
void forward(uint8_t speed) {
  // Left motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  // Right motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

// ✅ Swapped logic: Backward = earlier forward direction
void backward(uint8_t speed) {
  // Left motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  // Right motor
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void leftTurn(uint8_t speed) {
  // Left motor backward, right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void rightTurn(uint8_t speed) {
  // Left motor forward, right motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("🛑 Motors stopped.");
}
