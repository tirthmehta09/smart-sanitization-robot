#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// ----------------- Pin Definitions -----------------
#define DHTPIN 13
#define TRIG_PIN 5
#define ECHO_PIN 18
#define PIR_PIN 26
#define IR_LEFT_PIN 32
#define IR_RIGHT_PIN 33
#define WATER_SENSOR_PIN 34

// OLED I2C pins
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ----------------- Sensor Setup -----------------
DHT dht(DHTPIN, DHT11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ----------------- Setup -----------------
void setup() {
  Serial.begin(115200);

  // Initialize sensors
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(IR_LEFT_PIN, INPUT);
  pinMode(IR_RIGHT_PIN, INPUT);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Sanitization Bot Init");
  display.display();
  delay(2000);
}

// ----------------- Ultrasonic Function -----------------
long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1; // timeout
  return duration * 0.034 / 2;
}

// ----------------- Loop -----------------
void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  // --- DHT11 (Temp & Humidity) ---
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (!isnan(h) && !isnan(t)) {
    Serial.printf("Temp: %.2f C | Humidity: %.2f %%\n", t, h);
    display.printf("T: %.1fC  H: %.1f%%\n", t, h);
  } else {
    Serial.println("DHT11 Error");
    display.println("DHT11 Error");
  }

  // --- Ultrasonic Distance ---
  long distance = readDistanceCM();
  if (distance > 0) {
    Serial.printf("Distance: %ld cm\n", distance);
    display.printf("Dist: %ld cm\n", distance);
  } else {
    Serial.println("Ultrasonic Timeout");
    display.println("Dist: Error");
  }

  // --- PIR Motion ---
  int pirVal = digitalRead(PIR_PIN);
  if (pirVal == HIGH) {
    Serial.println("Motion Detected!");
    display.println("PIR: Motion");
  } else {
    Serial.println("No Motion");
    display.println("PIR: Clear");
  }

  // --- IR Sensors ---
  int irLeft = digitalRead(IR_LEFT_PIN);
  int irRight = digitalRead(IR_RIGHT_PIN);
  Serial.printf("IR Left: %d | IR Right: %d\n", irLeft, irRight);
  display.printf("IR L:%d R:%d\n", irLeft, irRight);

  // --- Water Level (Analog) ---
  int waterLevel = analogRead(WATER_SENSOR_PIN);
  Serial.printf("Water ADC: %d\n", waterLevel);
  display.printf("Water:%d\n", waterLevel);

  display.display();
  Serial.println("-------------------");
  delay(2000);
}
