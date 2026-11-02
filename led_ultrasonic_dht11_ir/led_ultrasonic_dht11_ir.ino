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
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// IR Sensor Pins
#define IR1_PIN 27
#define IR2_PIN 26

long duration;
float distance;

// Timer control
unsigned long lastSwitch = 0;
int currentScreen = 0; // 0=Ultrasonic, 1=DHT, 2=IR1, 3=IR2

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);

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
    currentScreen = (currentScreen + 1) % 4; // cycle through 4 screens
    lastSwitch = currentMillis;
    Serial.print("Switched to screen: ");
    Serial.println(currentScreen);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  if (currentScreen == 0) {
    // --- Ultrasonic ---
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 10000); // timeout 10ms

    display.setCursor(0, 0);
    display.println("ULTRA");

    if (duration == 0) {
      Serial.println("Out of range");
      display.setCursor(0, 30);
      display.println("No Echo");
    } else {
      distance = duration * 0.034 / 2;
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      display.setCursor(0, 30);
      display.print(distance, 1);
      display.println(" cm");
    }
  } 
  else if (currentScreen == 1) {
    // --- DHT11 ---
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    display.setCursor(0, 0);
    display.println("DHT11");

    if (isnan(h) || isnan(t)) {
      Serial.println("DHT11 Error");
      display.setCursor(0, 30);
      display.println("Error");
    } else {
      Serial.print("Temp: ");
      Serial.print(t);
      Serial.print(" C, Hum: ");
      Serial.println(h);

      display.setCursor(0, 20);
      display.print("T:");
      display.print(t, 1);
      display.println("C");

      display.setCursor(0, 45);
      display.print("H:");
      display.print(h, 1);
      display.println("%");
    }
  } 
  else if (currentScreen == 2) {
    // --- IR1 ---
    int ir1 = digitalRead(IR1_PIN);
    display.setCursor(0, 0);
    display.println("IR1");

    if (ir1 == LOW) {
      Serial.println("IR1: Block");
      display.setCursor(0, 30);
      display.println("Block");
    } else {
      Serial.println("IR1: Clear");
      display.setCursor(0, 30);
      display.println("Clear");
    }
  } 
  else if (currentScreen == 3) {
    // --- IR2 ---
    int ir2 = digitalRead(IR2_PIN);
    display.setCursor(0, 0);
    display.println("IR2");

    if (ir2 == LOW) {
      Serial.println("IR2: Block");
      display.setCursor(0, 30);
      display.println("Block");
    } else {
      Serial.println("IR2: Clear");
      display.setCursor(0, 30);
      display.println("Clear");
    }
  }

  display.display();
}
