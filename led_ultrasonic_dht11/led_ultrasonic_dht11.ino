#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ultrasonic Pins
#define TRIG_PIN 12
#define ECHO_PIN 13

// DHT11 Pins
#define DHTPIN 14        // GPIO14 for DHT11 data
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

long duration;
float distance;

// Timer control
unsigned long lastSwitch = 0;
bool showUltrasonic = true;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  dht.begin();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();

  // Switch every 2 seconds
  if (currentMillis - lastSwitch >= 2000) {
    showUltrasonic = !showUltrasonic;
    lastSwitch = currentMillis;
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  if (showUltrasonic) {
    // Ultrasonic Measurement
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms

    if (duration == 0) {
      Serial.println("Out of range");
      display.setCursor(0, 20);
      display.println("Out of");
      display.setCursor(0, 40);
      display.println("Range");
    } else {
      distance = duration * 0.034 / 2;
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      display.setCursor(0, 20);
      display.print(distance, 1);
      display.println(" cm");
    }
  } else {
    // DHT11 Measurement
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("DHT11 Error");
      display.setCursor(0, 20);
      display.println("DHT Error");
    } else {
      Serial.print("Temp: ");
      Serial.print(t);
      Serial.print(" °C  Hum: ");
      Serial.print(h);
      Serial.println(" %");

      display.setCursor(0, 10);
      display.print("T: ");
      display.print(t, 1);
      display.println(" C");

      display.setCursor(0, 40);
      display.print("H: ");
      display.print(h, 1);
      display.println(" %");
    }
  }

  display.display();
}
