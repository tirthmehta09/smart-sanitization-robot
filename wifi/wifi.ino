#include <WiFi.h>

const char* ssid = "Tirthraj-4G";       // your hotspot name
const char* password = "CHANGE_ME";   // set the robot hotspot password before flashing // your hotspot password

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("Connecting to hotspot...");

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected to hotspot!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to hotspot. Check SSID/band/signal.");
  }
}

void loop() {
  // Optional: Check connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠️ WiFi disconnected. Trying to reconnect...");
    WiFi.reconnect();
    delay(5000);
  }
}
