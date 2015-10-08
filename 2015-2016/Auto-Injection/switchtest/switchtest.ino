int pin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
  
}

void loop() {
  int val = digitalRead(pin);
  Serial.println(val);
}
