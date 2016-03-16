int ammeter = A1;

void setup() 
{
  Serial.begin(9600);
}

float ReadVout(float t, float v)
  {
    float total_delay = t;
    float value_delay = v;
    float voltage_sum = 0.0, Vout = 0.0;
    int i = 0, count = 0;
    while(i<=total_delay)
    {
      delay(value_delay);
      voltage_sum += (analogRead(ammeter)*5./1023.);
      count++;
      i += value_delay;
    }
    Vout = voltage_sum/count;
    return Vout;
  }
  
float ReadCurrent(float Vout)
  {
    float Vref = 2.85;
    //Vmax = 0;
    //double Cmax = 0.013;
    //double ratio = (Vout-Vref)/(Vmax-Vref);
    //double current = ratio*Cmax;
    float current = (Vout - Vref)*(0.160/125.0);
    return current*1000;
  }
  
String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}

void loop() 
{
  //Serial.print("Raw value: ");
  //Serial.println(analogRead(ammeter));
  float Vout = ReadVout(100, 3);
  //double Vout = analogRead(ammeter)*5./1023.;
  Serial.print("Vo(V): ");
  Serial.println(floatPrint(Vout));
  float current = ReadCurrent(Vout);
  Serial.print("Current(mA): ");
  Serial.println(floatPrint(current*1000));
  delay(500);
}

