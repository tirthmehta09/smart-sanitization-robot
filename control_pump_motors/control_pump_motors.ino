#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Control";     // WiFi Hotspot name
const char* password = "CHANGE_ME";   // set the robot hotspot password before flashing      // WiFi Hotspot password

WebServer server(80);

// UNO connected via Serial2
// TX2 (ESP32) -> RX (Arduino UNO pin 0)
// RX2 (ESP32) -> TX (Arduino UNO pin 1)
#define RXD2 16
#define TXD2 17

void handleRoot() {
  String page = 
  "<html>"
  "<head>"
  "<title>Robot + Pump Control</title>"
  "<style>"
  "body {text-align:center; font-family: Arial; background:#f4f4f4;}"
  "h2 {color:#333;}"
  "button {width:120px; height:60px; font-size:18px; margin:10px;"
  "border:none; border-radius:10px; background:#007bff; color:white;}"
  "button:hover {background:#0056b3;}"
  "</style>"
  "</head>"
  "<body>"
  "<h2>ESP32 Robot & Pump Controller</h2>"
  "<div>"
  "<button onclick=\"sendCmd('F')\">Forward</button><br>"
  "<button onclick=\"sendCmd('L')\">Left</button>"
  "<button onclick=\"sendCmd('S')\">Stop</button>"
  "<button onclick=\"sendCmd('R')\">Right</button><br>"
  "<button onclick=\"sendCmd('B')\">Backward</button>"
  "</div><hr>"
  "<h3>Pump Controls</h3>"
  "<div>"
  "<button onclick=\"sendCmd('P')\">Turn ON Pumps</button>"
  "<button onclick=\"sendCmd('p')\">Turn OFF Pumps</button><br>"
  "</div>"
  "<script>"
  "function sendCmd(cmd){"
  " fetch('/cmd?val='+cmd);"
  "}"
  "</script>"
  "</body>"
  "</html>";

  server.send(200, "text/html", page);
}

void handleCommand() {
  if (server.hasArg("val")) {
    char cmd = server.arg("val")[0];
    Serial2.write(cmd);  // send command to Arduino UNO
    Serial.println(String("Sent command: ") + cmd);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Create Access Point (Hotspot)
  WiFi.softAP(ssid, password);
  Serial.print("Access Point started. IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/cmd", handleCommand);
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}
