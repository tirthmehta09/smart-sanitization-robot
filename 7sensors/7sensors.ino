#include <Wire.h>
#include "DHT.h"

// ---------------- Pin Definitions ----------------
#define TRIG_PIN 12
#define ECHO_PIN 13

#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define IR1_PIN 27
#define IR2_PIN 26

#define WATER_PIN 34

#define PIR_PIN 25

#define LINE_LEFT 32
#define LINE_CENTER 33
#define LINE_RIGHT 35

// Variables
long duration;
float distance;

// Timer
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 5000; // 5s

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  dht.begin();

  Serial.println("System Init Done");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = currentMillis;

    Serial.println("\n===== Sensor Snapshot =====");

    // --- Ultrasonic ---
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 20000); // timeout 20ms
    if (duration == 0) {
      Serial.println("Ultrasonic: Out of range");
    } else {
      distance = duration * 0.034 / 2;
      Serial.printf("Ultrasonic Distance: %.1f cm\n", distance);
    }

    // --- DHT11 ---
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("DHT11 Error");
    } else {
      Serial.printf("Temp: %.1f C | Humidity: %.1f %%\n", t, h);
    }

    // --- IR sensors ---
    int ir1 = digitalRead(IR1_PIN);
    int ir2 = digitalRead(IR2_PIN);
    Serial.printf("IR1: %s | IR2: %s\n", ir1 == LOW ? "Block" : "Clear", ir2 == LOW ? "Block" : "Clear");

    // --- Water Level ---
    int waterValue = analogRead(WATER_PIN);
    int waterPercent = map(waterValue, 0, 4095, 0, 100);
    Serial.printf("Water Level: %d (raw), %d%%\n", waterValue, waterPercent);

    // --- PIR ---
    int pirVal = digitalRead(PIR_PIN);
    Serial.printf("PIR: %s\n", pirVal == HIGH ? "Motion Detected" : "No Motion");

    // --- Line Follower ---
    int leftVal = analogRead(LINE_LEFT);
    int centerVal = analogRead(LINE_CENTER);
    int rightVal = analogRead(LINE_RIGHT);
    Serial.printf("Line Sensors -> L:%d  C:%d  R:%d\n", leftVal, centerVal, rightVal);

    Serial.println("===========================\n");
  }
}
