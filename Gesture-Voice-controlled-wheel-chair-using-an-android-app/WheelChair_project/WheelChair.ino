#include <SoftwareSerial.h>
SoftwareSerial mybluetooth(2, 3);


int forward_led = 19; 
int back_led = 18;
int right_led = 17;
int left_led = 16;

// Definitions Arduino pins connected to input H Bridge
int IN1 = 12;
int IN2 = 11;
//int speedPinA = 11; // Needs to be a PWM pin to be able to control motor speed

int IN3 = 10;
int IN4 = 9;
//int speedPinB = 3; // Needs to be a PWM pin to be able to control motor speed

int a = 0;
int b = 0;
//int item = 0 ;


String readString;
void setup()
{

 mybluetooth.begin(9600);
 Serial.begin(9600);
 // Set the output pins
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);

 pinMode(forward_led , OUTPUT); 
 pinMode(back_led , OUTPUT);
 pinMode(right_led , OUTPUT);
 pinMode(left_led , OUTPUT);

}
  
void loop()

{
  
  digitalWrite(forward_led, LOW);    
  digitalWrite(back_led, LOW);
  digitalWrite(right_led, LOW);
  digitalWrite(left_led, LOW);

 //analogWrite(speedPinA, a); // Sets speed variable via PWM
 //analogWrite(speedPinB, b); // Sets speed variable via PWM
 
/////////////////////////////MOTOR A////////////////////////
digitalWrite(IN1, HIGH);
digitalWrite(IN2, HIGH);
////////////MOTOR B////////////
digitalWrite(IN3, HIGH);
digitalWrite(IN4, HIGH);

 while (mybluetooth.available()) { // listen for imformation from bluetooth
  delay(50);
 char t = mybluetooth.read();

 readString += t;
//Serial.println(t);

}

if(readString.length() > 0){
 
  Serial.println(readString);

if (readString == "1"||readString == "forward"){ 
///////////////////////FORWARD MOVEMENT///////////////
////////////MOTOR A////////////
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
////////////MOTOR B////////////
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);

 Serial.println("forward");
 
 digitalWrite(forward_led, HIGH);    
 digitalWrite(back_led, LOW);
 digitalWrite(right_led, LOW);
 digitalWrite(left_led, LOW);

delay(2000);
//item = 0;

//int t = mybluetooth.read();

}
 if (readString == "2"||readString == "backward"){
////////////////REVERSE MOVEMENT////////////////
////////////MOTOR A////////////
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 ////////////MOTOR B////////////
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 Serial.println("backward");
//---------------------------//
digitalWrite(forward_led, LOW);    
 digitalWrite(back_led, HIGH);
 digitalWrite(right_led, LOW);
 digitalWrite(left_led, LOW);

delay(2000);
//item = 0;
 
// int t = mybluetooth.read();

 }
 
 if (readString == "3"||readString == "right") 
 {   
 //////////////RIGHT TURN////////////////// 
/////////////MOTOR A/////////
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 ////////////MOTOR B////////////
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
 //delay(500);
 Serial.println("Right");
 //---------------------------//
 digitalWrite(forward_led, LOW);    
 digitalWrite(back_led, LOW);
 digitalWrite(right_led, HIGH);
 digitalWrite(left_led, LOW);
 delay(2000);
 //item = 0;
 
 }
   
  if (readString == "4"||readString == "left")
  {
 
  ///////////////LEFT TURN////////////////////
 ////////////MOTOR A////////////
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 ////////////MOTOR B//////////// 
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 
  Serial.println("Left");
//---------------------------//
 digitalWrite(forward_led, LOW);    
 digitalWrite(back_led, LOW);
 digitalWrite(right_led, LOW);
 digitalWrite(left_led, HIGH);

delay(2000);
//item = 0;
  }
  readString = "";
}
}
