// === Automatic pump cycle (Arduino Uno, Active-LOW relays) ===
// Pump1 -> D7, Pump2 -> D8

const int PUMP1_PIN = 8;
const int PUMP2_PIN = 9;
const unsigned long ON_TIME  = 7000UL;  // 7 seconds ON
const unsigned long OFF_TIME = 3000UL;  // 3 seconds OFF

bool pumpsOn = false;
unsigned long lastChange = 0;
unsigned long interval = OFF_TIME;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP1_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);

  // Start OFF (for active-LOW relay, HIGH = off)
  digitalWrite(PUMP1_PIN, HIGH);
  digitalWrite(PUMP2_PIN, HIGH);

  Serial.println("Auto pump cycle started (Active-LOW relays)");
  lastChange = millis();
}

void loop() {
  unsigned long now = millis();
  if (now - lastChange >= interval) {
    pumpsOn = !pumpsOn;
    if (pumpsOn) {
      // Turn pumps ON (LOW signal)
      digitalWrite(PUMP1_PIN, LOW);
      digitalWrite(PUMP2_PIN, LOW);
      interval = ON_TIME;
      Serial.println("PUMPS ON");
    } else {
      // Turn pumps OFF (HIGH signal)
      digitalWrite(PUMP1_PIN, HIGH);
      digitalWrite(PUMP2_PIN, HIGH);
      interval = OFF_TIME;
      Serial.println("PUMPS OFF");
    }
    lastChange = now;
  }
}
