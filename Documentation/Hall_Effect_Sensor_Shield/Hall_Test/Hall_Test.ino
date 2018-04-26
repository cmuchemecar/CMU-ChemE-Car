int hallEffectPin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(hallEffectPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("HAL VAL: ");
  Serial.println(digitalRead(hallEffectPin)); //This will print out the value of the sensor to the serial port
}
