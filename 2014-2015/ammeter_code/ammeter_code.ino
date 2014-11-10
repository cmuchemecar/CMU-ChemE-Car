int ammeter = A1;

void setup() 
{
  Serial.begin(9600);
  // make the pushbutton's pin an input:
}

double ReadVout(double t, double v)
  {
    double total_delay = t;
    double value_delay = v;
    double voltage_sum = 0, Vout = 0;
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
double ReadCurrent(double t, double v)
  {
    double Vout = ReadVout(t,v);
    double Vref = 1.0, Vmax = 4.0;
    double Cmax = 2;
    double ratio = (Vout-Vref)/(Vmax-Vref);
    double current = ratio*Cmax;
    return current;
  }
  
// the loop routine runs over and over again forever:
void loop() 
{
  // read the input pin:
  // print out the state of the button:
  //Serial.print("Raw value:");
  //Serial.println(analogRead(ammeter));
  Serial.print("Vo(V): ");
  Serial.println(ReadVout(100,3));
  Serial.print("Current(A): ");
  Serial.println(ReadCurrent(100,3));
  delay(500);        // delay in between reads for stability
}

