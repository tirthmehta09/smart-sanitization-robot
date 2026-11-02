#define WATER_SENSOR_PIN 34   // Use an ADC pin (ESP32 has many: 32–39)
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  int waterValue = analogRead(WATER_SENSOR_PIN);  // Range 0–4095
  float percentage = (waterValue / 4095.0) * 100; // Convert to %
  Serial.print("Raw Value: ");
  Serial.print(waterValue);
  Serial.print(" | Water Level: ");
  Serial.print(percentage);
  Serial.println(" %");
  delay(1000);
}