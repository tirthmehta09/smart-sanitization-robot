// ===== Automatic Pump Cycle for ESP32 =====
// Turns relay ON for 3s, OFF for 3s continuously

const int RELAY_PIN = 23;         // Relay signal pin
const bool ACTIVE_LOW = false;    // <-- Relay is active HIGH in your case

// Timing in milliseconds
const unsigned long ON_TIME  = 3000UL;
const unsigned long OFF_TIME = 3000UL;

bool isOn = false;
unsigned long lastChange = 0;
unsigned long interval = OFF_TIME;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);

  // Start OFF
  if (ACTIVE_LOW)
    digitalWrite(RELAY_PIN, HIGH);
  else
    digitalWrite(RELAY_PIN, LOW);

  Serial.println("ESP32 Auto Pump Cycle Started...");
  lastChange = millis();
}

void loop() {
  unsigned long now = millis();

  if (now - lastChange >= interval) {
    isOn = !isOn;  // Toggle state
    if (isOn) {
      Serial.println("PUMP ON");
      if (ACTIVE_LOW)
        digitalWrite(RELAY_PIN, LOW);
      else
        digitalWrite(RELAY_PIN, HIGH);
      interval = ON_TIME;
    } else {
      Serial.println("PUMP OFF");
      if (ACTIVE_LOW)
        digitalWrite(RELAY_PIN, HIGH);
      else
        digitalWrite(RELAY_PIN, LOW);
      interval = OFF_TIME;
    }
    lastChange = now;
  }
}
