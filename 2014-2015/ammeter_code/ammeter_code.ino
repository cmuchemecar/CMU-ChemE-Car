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
    double voltage_sum = 0.0, Vout = 0.0;
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
    return Vout;
    double Vref = 1.0, Vmax = 4.0;
    double Cmax = 2.0;
    double ratio = (Vout-Vref)/(Vmax-Vref);
    double current = ratio*Cmax;
    return current;
  }
  
void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC) ;
} 
  
// the loop routine runs over and over again forever:
void loop() 
{
  // read the input pin:
  // print out the state of the button:
  //Serial.print("Raw value:");
  //Serial.println(analogRead(ammeter));
  Serial.print("Vo(V): ");
  printDouble(ReadVout(100,3), 1000000);
  Serial.print("Current(A): ");
  printDouble(ReadCurrent(100,3), 1000000);
  delay(500);        // delay in between reads for stability
}

