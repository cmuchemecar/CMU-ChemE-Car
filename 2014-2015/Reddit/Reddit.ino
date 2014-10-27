void setup(){ Serial.begin(9600); }

void loop(){
    float currentValue = analogRead(1);
    Serial.print("raw val is ");
    Serial.println(String(int(currentValue)));
    float amps = (.0049 * (currentValue) - 2.5)/.066;
    Serial.print("  Amps = ");
    Serial.print(amps);
    Serial.print(" mA \n");
    delay(1000);
}

