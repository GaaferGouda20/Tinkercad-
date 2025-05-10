// Arduino code to run CubeSat circuit
// C++ Code

#include <Adafruit_LiquidCrystal.h>
#include <math.h>

Adafruit_LiquidCrystal lcd_1(0);

int seconds = 0;
int lightValue;
float height; // m
float g = 9.80665; // m/s^2
float propacc = 2*g;
float x, y, z, a, b, c; // Temporary variables for calculation purposes
float t1 ,t2 ,t3 ,t4 ,t5 ,t6;
int var;

// g(h) = g / ( 1 + h/Re )^2
// s = u*t + (a*t^2)/2
// v = u + a*t
// v^2 = u^2 + 2*a*s

void setup()
{
	// put your setup code here, to run once:
    float seconds = 0;
    pinMode(4, OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(2,OUTPUT);
   	Serial.begin(9600);
    lcd_1.begin(16,2);
  	Serial.print("This is a program that controls the circuitry of the CubeSat");
  	Serial.print('\n');
    Serial.print("Enter the altitude in metres above which the CubeSat is dropped: ");
    lcd_1.print("Satellite Clock");
}

void loop()
{
	while (Serial.available() != 0)
  	{
      height = Serial.parseFloat();
      Serial.print(height);
      x = 2*height;
      y = x/g;
      z = sqrt(y);
      t1 = z;
      t2 = t1/2;
      a = g*height;
      b = sqrt(a);
      c = height/6;
      t3 = 10 + ( c + b )/propacc;
      t4 = 10 + ( height + b )/propacc;
      Serial.print('\n');
      Serial.print("The time for which LED1 glows is: ");
      Serial.print(t2);
      Serial.print(" seconds");
      Serial.print('\n');
      Serial.print("The time after which LED2 lights up is: ");
      Serial.print(t2);
      Serial.print(" seconds");
      Serial.print('\n');
      Serial.print("The time after which the LED3 lights up is: ");
      Serial.print(t3);
      Serial.print(" seconds");
      Serial.print('\n');
      Serial.print("The time after which the engine fires is: ");
      Serial.print(t2);
      Serial.print(" seconds");
      Serial.print('\n');
      Serial.print("The propeller provides a maximum acceleration of 2g");
      Serial.print('\n');
      Serial.print("The speed of the CubeSat when it crosses the half-line is: ");
      Serial.print(b);
      Serial.print('\n');
      Serial.print("The CubeSat finally lands after ");
      Serial.print(t4);
      Serial.print(" seconds");
      Serial.print('\n');
      var = 1;
    }
  	
  	if ( var == 1)
  	{
      lcd_1.setCursor(0,1);
      lcd_1.print(seconds);
      lcd_1.setBacklight(1);
      delay(1000);
      seconds += 1;
      
      lightValue = analogRead(A0);
      if (lightValue < 500)
      {
        digitalWrite(13,HIGH);
      }
      else
      {
        digitalWrite(13,LOW);
      }

      if (seconds < t2)
       {
         digitalWrite(12,HIGH);
         digitalWrite(11,LOW);
         digitalWrite(2,LOW);
         digitalWrite(10,LOW);
       }

       if (seconds > t2 && seconds < t3)
       {
         digitalWrite(12,LOW);
         digitalWrite(11,HIGH);
         digitalWrite(2,HIGH);
         digitalWrite(10,LOW);
       }

       if (seconds > t3 and seconds < t4)
       {
         digitalWrite(12,LOW);
         digitalWrite(11,HIGH);
         digitalWrite(2,HIGH);
         digitalWrite(10,HIGH);
       }

       if (seconds > t4)
       {
         digitalWrite(12,HIGH);
         digitalWrite(12,HIGH);
         digitalWrite(10,HIGH);
         digitalWrite(2,HIGH);
       }
  	}
}