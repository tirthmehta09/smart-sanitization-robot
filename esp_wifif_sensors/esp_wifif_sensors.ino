#include <WiFi.h>
#include <WebServer.h>

// === WiFi Setup (Access Point Mode) ===
const char* ssid = "ESP32_Control";
const char* password = "CHANGE_ME";   // set the robot hotspot password before flashing

WebServer server(80);

// === Serial connection with UNO ===
#define RXD2 16
#define TXD2 17

// === Sensor Pins ===
#define TRIG_FRONT 12
#define ECHO_FRONT 14
#define TRIG_LEFT 26
#define ECHO_LEFT 25
#define TRIG_RIGHT 33
#define ECHO_RIGHT 32

#define IR1 34
#define IR2 35
#define WATER_LEVEL 27

// === Globals ===
long duration;
float distFront, distLeft, distRight;
int ir1Val, ir2Val;
int waterLevelVal;

// === Functions ===
float readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  float distance = duration * 0.034 / 2;
  if (distance == 0 || distance > 400) return -1; // invalid
  return distance;
}

void readSensors() {
  distFront = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
  distLeft  = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  distRight = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
  ir1Val = digitalRead(IR1);
  ir2Val = digitalRead(IR2);
  waterLevelVal = analogRead(WATER_LEVEL);
}

void handleRoot() {
  readSensors();

  String page = "<html><head><title>ESP32 Robot + Sensors</title>"
  "<meta http-equiv='refresh' content='3'/>" // auto refresh every 3 sec
  "<style>"
  "body {font-family:Arial; text-align:center; background:#f2f2f2;}"
  "button {width:120px; height:60px; font-size:18px; margin:10px;"
  "border:none; border-radius:10px; background:#007bff; color:white;}"
  "button:hover {background:#0056b3;}"
  "table {margin:auto; border-collapse:collapse; background:#fff;}"
  "td,th {padding:10px; border:1px solid #ccc;}"
  "</style></head><body>";

  page += "<h2>🤖 ESP32 Robot Dashboard</h2>";

  // === Motor Controls ===
  page += "<h3>Motor Controls</h3>"
          "<button onclick=\"sendCmd('F')\">Forward</button><br>"
          "<button onclick=\"sendCmd('L')\">Left</button>"
          "<button onclick=\"sendCmd('S')\">Stop</button>"
          "<button onclick=\"sendCmd('R')\">Right</button><br>"
          "<button onclick=\"sendCmd('B')\">Backward</button><hr>";

  // === Pump Controls ===
  page += "<h3>💧 Pump Controls</h3>"
          "<button onclick=\"sendCmd('P')\">ON</button>"
          "<button onclick=\"sendCmd('p')\">OFF</button><hr>";

  // === Sensor Data Table ===
  page += "<h3>📟 Live Sensor Readings</h3>"
          "<table>"
          "<tr><th>Sensor</th><th>Value</th></tr>";

  page += "<tr><td>Front Ultrasonic</td><td>" + String(distFront, 1) + " cm</td></tr>";
  page += "<tr><td>Left Ultrasonic</td><td>" + String(distLeft, 1) + " cm</td></tr>";
  page += "<tr><td>Right Ultrasonic</td><td>" + String(distRight, 1) + " cm</td></tr>";
  page += "<tr><td>IR Sensor 1</td><td>" + String(ir1Val ? "No Obstacle" : "Obstacle") + "</td></tr>";
  page += "<tr><td>IR Sensor 2</td><td>" + String(ir2Val ? "No Obstacle" : "Obstacle") + "</td></tr>";
  page += "<tr><td>Water Level</td><td>" + String(waterLevelVal) + " / 4095</td></tr>";
  page += "</table><hr>";

  page += "<script>function sendCmd(cmd){fetch('/cmd?val='+cmd);}</script>"
          "</body></html>";

  server.send(200, "text/html", page);
}

void handleCommand() {
  if (server.hasArg("val")) {
    char cmd = server.arg("val")[0];
    Serial2.write(cmd);
    Serial.println(String("Sent command: ") + cmd);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Missing val");
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Ultrasonic Pins
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  // IR + Water Level
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(WATER_LEVEL, INPUT);

  // Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  Serial.print("✅ AP Started | IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/cmd", handleCommand);
  server.begin();
  Serial.println("HTTP Server Ready!");
}

void loop() {
  server.handleClient();
}