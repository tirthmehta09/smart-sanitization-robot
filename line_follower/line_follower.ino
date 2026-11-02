#define LEFT_SENSOR   32
#define CENTER_SENSOR 33
#define RIGHT_SENSOR  35

void setup() {
  Serial.begin(115200);
}

void loop() {
  int leftVal   = analogRead(LEFT_SENSOR);
  int centerVal = analogRead(CENTER_SENSOR);
  int rightVal  = analogRead(RIGHT_SENSOR);

  Serial.print("L: ");
  Serial.print(leftVal);
  Serial.print("  C: ");
  Serial.print(centerVal);
  Serial.print("  R: ");
  Serial.println(rightVal);

  delay(1000);
}
