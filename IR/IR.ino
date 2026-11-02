#define IR1_PIN 32
#define IR2_PIN 33
 
void setup() {
  Serial.begin(115200);   // Match with Serial Monitor
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
}
 
void loop() {
  int ir1 = digitalRead(IR1_PIN);
  int ir2 = digitalRead(IR2_PIN);
 
  Serial.print("IR1: ");
  Serial.print(ir1);
  Serial.print(" | IR2: ");
  Serial.println(ir2);
 
  delay(1000);
}