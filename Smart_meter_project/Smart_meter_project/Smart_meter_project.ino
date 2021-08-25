#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
 
SoftwareSerial serialSIM800(2,3);

LiquidCrystal_I2C lcd(0x27,20,4); 

const int seal_Pin = 8;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int seal_State = 0;      

void setup() {
 
  Serial.begin(9600);
  while(!Serial);
  serialSIM800.begin(9600);

  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(seal_Pin, INPUT);
 
 
}

void loop() {
  
seal_State = digitalRead(seal_Pin);

  if (seal_State == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    
lcd.clear();    
lcd.setCursor(0,0);
lcd.print("Warning:");
lcd.setCursor(0,1);
lcd.print("The Seal has been");
lcd.setCursor(0,2);
lcd.print("Tempered"); 
    // turn LED off:
    digitalWrite(ledPin, LOW);
    send_text();
  }
  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Credit/Ghc:50");
lcd.setCursor(0,1);
lcd.print("Duration/Day(s):20");
lcd.setCursor(0,2);
lcd.print("Voltage/V(AC):220");
lcd.setCursor(0,3);
lcd.print("Current/Amp(s):2");
delay(500);

}  

void send_text(){
      
serialSIM800.write("AT+CMGF=1\r\n");
delay(2000);
serialSIM800.write("AT+CMGS=\"enter your number\"\r\n");// Number to be changed
delay(2000);
serialSIM800.println("Theft detected");
delay(500);
serialSIM800.println("Meter Number 00015");
delay(500);
serialSIM800.println("House Number 43");
delay(500);
serialSIM800.println("Sakumono");
delay(500);
serialSIM800.write(0X1A);
delay(50000);
  }






