#define TRIG_PIN 12
#define ECHO_PIN 13

long duration;
float distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  // Clear trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10µs pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo with timeout
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout

  // If no pulse received
  if (duration == 0) {
    Serial.println("Out of range");
  } else {
    // Convert time to distance (cm)
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(5000); // update twice per second
}
