#define switchpin 7

void setup() {
  pinMode(switchpin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(switchpin, LOW);
  delay(1000);
}

void loop() {
  digitalWrite(switchpin, HIGH);
  delay(1000);
  digitalWrite(switchpin, LOW);
  delay(1000);
}
