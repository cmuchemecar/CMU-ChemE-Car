int pin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  
}

void loop() {
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(3000);
}
