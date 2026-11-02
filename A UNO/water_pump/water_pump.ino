// === Automatic Pump Control (Arduino Uno) ===
// Turns pump ON for 3 seconds, OFF for 3 seconds repeatedly

const int RELAY_PIN = 7;       // D7 -> Relay IN
const unsigned long ON_TIME  = 3000UL; // 3 seconds ON
const unsigned long OFF_TIME = 3000UL; // 3 seconds OFF

// Change this if your relay is active-low (turns on when input = LOW)
const bool ACTIVE_LOW = false;

unsigned long lastChange = 0;
bool isOn = false;
unsigned long interval = OFF_TIME;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  // Start OFF
  if (ACTIVE_LOW) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);

  isOn = false;
  lastChange = millis();
  interval = OFF_TIME;

  Serial.println("Auto pump cycle started (Arduino Uno)");
}

void loop() {
  unsigned long now = millis();
  if (now - lastChange >= interval) {
    // toggle pump state
    isOn = !isOn;

    if (isOn) {
      if (ACTIVE_LOW) digitalWrite(RELAY_PIN, LOW);
      else digitalWrite(RELAY_PIN, HIGH);
      interval = ON_TIME;
      Serial.println("[STATE] Pump ON");
    } else {
      if (ACTIVE_LOW) digitalWrite(RELAY_PIN, HIGH);
      else digitalWrite(RELAY_PIN, LOW);
      interval = OFF_TIME;
      Serial.println("[STATE] Pump OFF");
    }

    lastChange = now;
  }

  // add other non-blocking logic here if needed
}
