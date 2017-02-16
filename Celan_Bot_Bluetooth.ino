#define mop 6
#define pump 7
#define dcm_L0 8
#define dcm_L1 9 
#define dcm_r0 10 
#define dcm_r1 11
#define onesquare 1000
#define rightangle 1000
const int trigPin = 2;
int  duration;
int  distance;
int threshold = 10;
const int echoPin = 4;
void allactionstop(void);
int state = 5;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(mop ,OUTPUT);
  pinMode(pump ,OUTPUT);
  pinMode(dcm_L0 ,OUTPUT);
  pinMode(dcm_L1 ,OUTPUT);
  pinMode(dcm_r0 ,OUTPUT);
  pinMode(dcm_r1 ,OUTPUT);
  Serial.begin(9600);
  forward();
  left();
  right();
  reverse();
  spraywater();
  mopfloor();
   allactionstop(); 
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available() > 0)
  {
    state =Serial.read(); // put your main code here, to run repeatedly:
  }
if (state == '5')
{
 allactionstop();
 state = 5;
}
else if (state == '2')
{
  forward();
  Serial.println("FRONT");
  state = 5;
}
else if (state == '3')
{
  spraywater();
  Serial.println("WATER ON");
  state =5;
}
else if (state =='4')
{
  left();
  allactionstop();
  Serial.println("LEFT");
  
  state =5;
}
else if (state =='6')
{
  right();
  Serial.println("RIGHT");
  state =5;
  
}
else if (state =='7')
{
  mopfloor();
  Serial.println("MOPING FLOOR");
  state =5;
}
else if (state == '8')
{
  reverse();
  Serial.println("REVERSE");
  state =5;
}
else if (state =='1')
{
  automode();
  state =5;
  Serial.println("AUTO MODE");
}
}
void allactionstop()
{
   digitalWrite(mop,LOW);
  digitalWrite(pump,LOW);
  digitalWrite(dcm_L0,LOW);
  digitalWrite(dcm_L1,LOW);
  digitalWrite(dcm_r0,LOW);
  digitalWrite(dcm_r1,LOW);
  delay(500);
  
}

void forward()
{
  distacecheck();
  digitalWrite(dcm_L0, LOW);
  digitalWrite(dcm_L1, HIGH);
  digitalWrite(dcm_r0, LOW);
  digitalWrite(dcm_r1, HIGH);
  delay (1000);
}

void reverse()
{
  digitalWrite(dcm_L0, HIGH);
  digitalWrite(dcm_L1, LOW);
  digitalWrite(dcm_r0, HIGH);
  digitalWrite(dcm_r1, LOW);
  delay (1000);
}

void left()
{
  digitalWrite(dcm_L0, LOW);
  digitalWrite(dcm_L1, LOW);
  digitalWrite(dcm_r0, LOW);
  digitalWrite(dcm_r1, HIGH);
  delay (1000);
}

void right()
{
  digitalWrite(dcm_L0, LOW);
  digitalWrite(dcm_L1, HIGH);
  digitalWrite(dcm_r0, LOW);
  digitalWrite(dcm_r1, LOW);
  delay (1000);
}
void spraywater()
{
  digitalWrite(pump,HIGH);
  delay(1000);
  digitalWrite(pump,LOW);
  delay(500);
}
void mopfloor()
{
  digitalWrite(mop,HIGH);
  delay(1000);
  digitalWrite(mop,LOW);
  delay(500);
}
 void automode()
 {

  int m=5,n=5,a,b,x,y; 
  x=m; y=n;             // m is the column of matrix and n is row
  a=0;b=0;              // start of square matrix location
 while(y>=0)
 {
  while(x>=0)
  {
    distacecheck();
    x = x-1;
    b= b+1;
    forward();
    delay(onesquare);
    mopfloor();
  }
  x=m;
  y = y-1;
  left();
  delay(rightangle);
  forward();
  delay(onesquare);
  mopfloor();
  left();
  delay(rightangle);
  while(x>=0)
  {
    distacecheck();
    x = x-1;
    b= b-1;
    forward();
    delay(onesquare);
    mopfloor();
  }
   x=m;
  y = y-1;
  right();
  delay(rightangle);
  forward();
  delay(onesquare);
  mopfloor();
  right();
  delay(rightangle);
  a = a+1;
 }
 }
 void distacecheck()
 {  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);
  if (distance <= threshold)
  {
    right();
    delay(500);
    forward();
    delay(1000);
    left();
    delay(500);
    
  }
 }
 long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
 

