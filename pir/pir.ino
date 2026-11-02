#define PIR_PIN 25

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  Serial.println("PIR Warm-up... wait 1 min");
}

void loop() {
  int pirVal = digitalRead(PIR_PIN);

  if (pirVal == HIGH) {
    Serial.println("🚨 Motion Detected!");
  } else {
    Serial.println("✅ No Motion");
  }

  delay(500); // shorter delay for smoother detection
}
