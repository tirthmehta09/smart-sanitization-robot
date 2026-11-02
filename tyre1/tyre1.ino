#define EN 21
#define IN1 18
#define IN2 19
 
void setup() {
  Serial.begin(115200);
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}
 
void loop() {
  Serial.println("Forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 200); // For ESP32, this may act as full ON depending on core
  delay(2000);
 
  Serial.println("Stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 0);
  delay(1000);
 
  Serial.println("Backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN, 200);
  delay(2000);
 
  Serial.println("Stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 0);
  delay(1000);
}
 