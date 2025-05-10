#define mr1 6
#define mr2 5
#define ml1 9
#define ml2 10
#define servo_pulse 7
#define triger 8

#include <Servo.h>
int distance, select, pos=0;
Servo myservo;
void setup() {
  Serial.begin(9600);
  myservo.attach(7);
for(int i=0 ; i<11 ; i++)
{
  pinMode(i, OUTPUT);
}


}
int getDistance()
// returns distance from Ping))) sensor in cm
{
int distance;
unsigned long pulseduration=0;
  
// get the raw measurement data from Ping)))
// set pin as output so we can send a pulse
pinMode(triger, OUTPUT);
  
// set output to LOW
digitalWrite(triger, LOW);
delayMicroseconds(5);
  
// send the 5uS pulse out to activate Ping)))
digitalWrite(triger, HIGH);
delayMicroseconds(5);
digitalWrite(triger, LOW);
  
// change the digital pin to input to read the incoming pulse
pinMode(triger, INPUT);
  
// measure the length of the incoming pulse
pulseduration=pulseIn(triger, HIGH);
  
// divide the pulse length in half
pulseduration=pulseduration/2;
  
// convert to centimeters
distance = int(pulseduration/29);
return distance;
}
  void goForward(){

  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
}
  void goBack(){

  digitalWrite(mr1,LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
}
void turnLeft()
{ 
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
}
void turnRight()
{
  digitalWrite(mr1,LOW);
  digitalWrite(mr2,HIGH);
  digitalWrite(ml1,HIGH);
  digitalWrite(ml2, LOW);
  
}
void STOP()
{

  digitalWrite(mr1,LOW);
  digitalWrite(mr2,LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
}
void loop() 
{

  Serial.print(distance);
  myservo.write(90);
  delay(15);
  distance = int (getDistance());
Serial.print(distance);
  while(distance >30 ) {
    goForward();
    distance=getDistance();
    
  }
while(distance <= 30)
{
  STOP();
  delay(1000);
  myservo.write(pos);
  select = pos;
  pos+=45;
  if(pos == 225)
  pos = 0;
  distance=getDistance();
  
  }
myservo.write(90);
switch(select){
    case 0:
    turnLeft();
    delay(250);
    STOP();
    break;
    case 45 :
    turnLeft();
    delay(500);
    STOP();
    break;
    case 135 :
    turnRight();
    delay(250);
    STOP();
    break;
    case 180 :
    turnRight();
    delay(500);
    STOP();
    break;
}
  
}

