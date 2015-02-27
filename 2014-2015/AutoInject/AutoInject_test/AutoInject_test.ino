void setup()
{
 Serial.begin(9600);
 
}
void loop(){
  delay(100);
  
  Serial.println(analogRead(3));
}

