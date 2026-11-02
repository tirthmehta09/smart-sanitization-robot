// === Dual Motor Test for L293 / ESP32 ===

// Left Motor Pins
#define ENA 13     // Enable pin (PWM)
#define IN1 14     // Direction 1
#define IN2 26     // Direction 2

// Right Motor Pins
#define ENB 12     // Enable pin (PWM)
#define IN3 27     // Direction 1
#define IN4 25     // Direction 2

void setup() {
  Serial.begin(115200);
  Serial.println("Dual Motor Test Starting...");

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // ---------- FORWARD ----------
  Serial.println("FORWARD");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Swapped logic for right motor (to correct direction)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 200);   // speed (0–255)
  analogWrite(ENB, 200);   // speed (0–255)
  delay(5000);

  // ---------- STOP ----------
  Serial.println("STOP");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(3000);
}
