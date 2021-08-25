#include <SoftwareSerial.h>
 #include <TinyGPS.h>

SoftwareSerial serialSIM800(10,11);
SoftwareSerial gpsSerial(4,5);//rx,tx

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
float lat = 0.0000,lon = 0.0000; // create variable for latitude and longitude object 

TinyGPS gps;
void setup() {
  serialSIM800.begin(9600);
 // pinMode(ledPin, OUTPUT);
 // pinMode(interruptPin, INPUT_PULLUP);
 // attachInterrupt(digitalPinToInterrupt(interruptPin), action, CHANGE);
}

void loop() {
 // digitalWrite(ledPin, state);


  for(int i=1;i++;i>3)
{
     gpsSerial.begin(9600); //open comunications with GPS
     //delay(60000);
    while(gpsSerial.available()){ // check for gps data
    if(gps.encode(gpsSerial.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    Serial.print("Position: ");
    Serial.print("Latitude: ");
    Serial.print(lat,6);
    Serial.print(";");
    Serial.print("Longitude: ");
    Serial.println(lon,6); 

    Serial.print(lat);
    Serial.print(" ");
    
   
    gpsSerial.end();// close communications with the GPS 
    delay(1000);
    }
   }
  }
  
  gpsSerial.end();
  String latitude = String(lat,6);
    String longitude = String(lon,6);
  Serial.println(latitude+";"+longitude);
// delay(60000);
 serialSIM800.begin(9600);
 action();
  serialSIM800.end();
  
}


void action() {
  serialSIM800.begin(9600); //open comunications with GSM
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(500);
  serialSIM800.write("AT+CMGS=\"0245248349\"\r\n");
  gprs.serialSIM800.println("http://maps.google.com/maps/?saddr=0.1,0.1");
  gprs.serialSIM800.println("&daddr=");
  delay(500);
  serialSIM800.println(lat,6);
  delay(500);
  serialSIM800.println(lon,6); 
  delay(500);
  serialSIM800.write(0X1A);
  delay(2000);     
  serialSIM800.end();
  delay(2000);
}
