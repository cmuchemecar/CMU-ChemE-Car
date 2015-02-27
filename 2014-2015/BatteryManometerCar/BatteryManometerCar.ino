#define HALL 0
#define DELTA 20
#define R 0.1
#define RAD 3.14
#define SAMPLETIME 5000

int pastTime;
int currentTime;
int pastHall;
int currentHall;
int t = 0;
float w = 0;
float v = 0;

void setup() {
  Serial.begin(9600);
  pinMode(HALL, INPUT);

  int pastHall = analogRead(HALL);
  int pastTime = millis();
}

void loop() {
  currentHall = analogRead(HALL);
  currentTime = millis();
  
  if (abs(currentHall - pastHall) > DELTA) {
    t = currentTime - pastTime;
    w = RAD/t;
    v = w * R;
    pastTime = currentTime;
  }
  
  if (abs(currentTime - pastTime) > SAMPLETIME) {
    Serial.println(floatPrint(v) + ", " + String(currentTime));
  }

  pastHall = currentHall;  
}

String floatPrint(float x){
  int intp = x;
  int fracp = (x - intp) * 1000;
  if(fracp < 0){
    fracp = -1 * fracp;
  }
  return (String(intp) + "." + String(fracp));
}
