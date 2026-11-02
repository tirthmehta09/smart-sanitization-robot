#include "DHT.h"

// Pin configuration
#define DHTPIN 14       // DHT11 signal pin connected to GPIO13 of ESP32
#define DHTTYPE DHT11    // Sensor type is DHT11

// Create DHT object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11 Sensor Reading Test");
  dht.begin();  // Initialize sensor
}

void loop() {
  // Read humidity (in %)
  float humidity = dht.readHumidity();
  // Read temperature (in °C)
  float temperature = dht.readTemperature();

  // Check if readings failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("❌ Failed to read from DHT11 sensor!");
    delay(2000);
    return;
  }

  // Print results to Serial Monitor
  Serial.print("🌡 Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  |  ");
  Serial.print("💧 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000); // Read every 2 seconds
}
