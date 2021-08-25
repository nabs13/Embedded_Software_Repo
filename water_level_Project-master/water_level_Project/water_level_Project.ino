
#include <SoftwareSerial.h>
int trig = 12;
int echo = 11;
int green_led = 6;
int yellow_led = 7;
int red_led = 8;
int pump = 5;
int buzzer = 9;
SoftwareSerial serialSIM800(3,2);

void setup()
{
  Serial.begin(9600);
  serialSIM800.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
pinMode(green_led,OUTPUT);
pinMode(yellow_led,OUTPUT);
pinMode(red_led,OUTPUT);
pinMode(buzzer,OUTPUT);

}

void loop()
{
  long t = 0, h = 0, hp = 0;
  
  // Transmitting pulse
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Waiting for pulse
  t = pulseIn(echo, HIGH);
  digitalWrite(green_led,LOW);
digitalWrite(yellow_led,LOW);
digitalWrite(red_led,LOW);
digitalWrite(pump,LOW);
  // Calculating distance 
  h = t / 58;
 
  h = h - 6;  // offset correction
  h = 50 - h;  // water height, 0 - 50 cm
  
  hp = 2 * h;  // distance in %, 0-100 %
  
  // Sending to computer
  Serial.print(hp);
  // Serial.print(" cm\n");
  Serial.print("\n");
  
  delay(1000);

if(hp <= 80)
{
  digitalWrite(green_led,HIGH);
digitalWrite(yellow_led,LOW);
digitalWrite(red_led,LOW);
digitalWrite(pump,HIGH);
//  delay(2000);
digitalWrite(buzzer,HIGH);
delay(5000); 

  }
if(hp>=81 && hp <= 95)
{
   digitalWrite(green_led,HIGH);
digitalWrite(yellow_led,HIGH);
digitalWrite(red_led,LOW);
 digitalWrite(buzzer,LOW);
digitalWrite(pump,HIGH);
 delay(4000);

  }
if(hp>=95)
{
  digitalWrite(green_led,HIGH);
digitalWrite(yellow_led,HIGH);
digitalWrite(red_led,HIGH); 
digitalWrite(buzzer,HIGH);
delay(1000); 
digitalWrite(buzzer,LOW);

serialSIM800.write("AT+CMGF=1\r\n");
delay(400);
serialSIM800.write("AT+CMGS=\"enter your number\"\r\n");
delay(400);
serialSIM800.println("The Tank is Full"); 
delay(400);
serialSIM800.write(0X1A);
delay(400);
 
  digitalWrite(pump,LOW);
  delay(60000); 

 //digitalWrite(pump,LOW);
  delay(2000); 
  }


  
}
