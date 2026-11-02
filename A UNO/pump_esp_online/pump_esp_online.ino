// === Arduino UNO: Pump Controller via Serial ===
// Active-LOW Relay Logic
// Pump1 -> D8, Pump2 -> D9

const int PUMP1_PIN = 8;
const int PUMP2_PIN = 9;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP1_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);

  // Start OFF
  digitalWrite(PUMP1_PIN, HIGH);
  digitalWrite(PUMP2_PIN, HIGH);

  Serial.println("UNO Pump Controller Ready");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {
      case 'A': // Pump 1 ON
        digitalWrite(PUMP1_PIN, LOW);
        Serial.println("Pump 1 ON");
        break;

      case 'a': // Pump 1 OFF
        digitalWrite(PUMP1_PIN, HIGH);
        Serial.println("Pump 1 OFF");
        break;

      case 'B': // Pump 2 ON
        digitalWrite(PUMP2_PIN, LOW);
        Serial.println("Pump 2 ON");
        break;

      case 'b': // Pump 2 OFF
        digitalWrite(PUMP2_PIN, HIGH);
        Serial.println("Pump 2 OFF");
        break;

      default:
        Serial.println("Unknown command");
        break;
    }
  }
}
