#include "DHT.h"

// ----------------- Pin Definitions -----------------
#define TRIG_PIN 12
#define ECHO_PIN 13

#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define IR1_PIN 27
#define IR2_PIN 26

#define WATER_PIN 34   // analog input

// ----------------- Globals -----------------
long duration;
float distance;

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 5000; // 5 sec

// ----------------- Setup -----------------
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);

  Serial.begin(115200);
  dht.begin();

  Serial.println("=== Starting Sensor Test (All Values) ===");
}

// ----------------- Ultrasonic -----------------
long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

// ----------------- Loop -----------------
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastRead >= READ_INTERVAL) {
    lastRead = currentMillis;

    Serial.println("\n----- SENSOR READINGS -----");

    // DHT11
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("DHT11: Error reading");
    } else {
      Serial.print("DHT11 -> Temp: ");
      Serial.print(t, 1);
      Serial.print(" C, Humidity: ");
      Serial.print(h, 1);
      Serial.println(" %");
    }

    // Ultrasonic
    long dist = readDistanceCM();
    if (dist < 0) {
      Serial.println("Ultrasonic: No Echo");
    } else {
      Serial.print("Ultrasonic -> Distance: ");
      Serial.print(dist);
      Serial.println(" cm");
    }

    // IR sensors
    int ir1 = digitalRead(IR1_PIN);
    int ir2 = digitalRead(IR2_PIN);
    Serial.print("IR1: ");
    Serial.print(ir1 == LOW ? "Block" : "Clear");
    Serial.print(" | IR2: ");
    Serial.println(ir2 == LOW ? "Block" : "Clear");

    // Water level (average)
    long sum = 0;
    for (int i = 0; i < 10; i++) {
      sum += analogRead(WATER_PIN);
      delay(5);
    }
    int waterValue = sum / 10;
    int waterPercent = map(waterValue, 0, 4095, 0, 100);

    Serial.print("Water Level -> Raw: ");
    Serial.print(waterValue);
    Serial.print(" | Percent: ");
    Serial.print(waterPercent);
    Serial.println("%");

    Serial.println("---------------------------");
  }
}
