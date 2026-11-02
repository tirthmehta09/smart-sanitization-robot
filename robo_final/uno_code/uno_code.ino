// === Arduino UNO: Motors + Pumps (Directions Corrected) ===
// Works with ESP32 dashboard via Serial
// Motors via L293D, Pumps via active-LOW relays

// === Motor Pins ===
const int IN1 = 2;   // Left Motor
const int IN2 = 3;
const int ENA = 5;   // PWM

const int IN3 = 4;   // Right Motor
const int IN4 = 7;
const int ENB = 6;   // PWM

// === Pump Pins ===
const int PUMP1_PIN = 8;
const int PUMP2_PIN = 9;

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Pump setup
  pinMode(PUMP1_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);

  stopMotors();
  digitalWrite(PUMP1_PIN, HIGH);
  digitalWrite(PUMP2_PIN, HIGH);

  Serial.println("✅ UNO ready: Motors + Pumps Controller");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {
      case 'F': forward(200); Serial.println("⬆️ Forward"); break;
      case 'B': backward(200); Serial.println("⬇️ Backward"); break;
      case 'L': leftTurn(200); Serial.println("⬅️ Left"); break;
      case 'R': rightTurn(200); Serial.println("➡️ Right"); break;
      case 'S': stopMotors(); Serial.println("🛑 Stop"); break;

      // ✅ Both pumps ON/OFF together
      case 'P':
        digitalWrite(PUMP1_PIN, LOW);
        digitalWrite(PUMP2_PIN, LOW);
        Serial.println("💧 Both Pumps ON");
        break;

      case 'p':
        digitalWrite(PUMP1_PIN, HIGH);
        digitalWrite(PUMP2_PIN, HIGH);
        Serial.println("💧 Both Pumps OFF");
        break;

      default:
        Serial.print("⚠️ Unknown command: ");
        Serial.println(cmd);
        break;
    }
  }
}

// === Movement Functions (Final Correct Logic) ===

// ✅ Forward
void forward(uint8_t speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

// ✅ Backward
void backward(uint8_t speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

// ✅ Left Turn (pivot)
void rightTurn(uint8_t speed) {
  // Left motor backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

// ✅ Right Turn (pivot)
void leftTurn(uint8_t speed) {
  // Left motor forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  // Right motor backward
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
}
