#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial mySerial(4, 3); // RX, TX
TinyGPSPlus gps ;




float longitude ;
float latitude ;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  
  mySerial.println("AT");
  delay(50);
  mySerial.println("AT+CGPSPWR=1");
  delay(50);
  mySerial.println("AT+CGPSSTATUS?");
  delay(200);
  mySerial.println("AT+CGPSINF=0"); 
  delay(200);
  mySerial.println("AT+CGPSOUT=32");
  delay(200);  

  
 }


void loop() {
 
 while (mySerial.available() > 0) // while we are getting data from mySerial
 {
   gps.encode(mySerial.read()) ; // read gps
   if (gps.location.isUpdated())  // if the location has been updated, print the data
   {
     longitude = gps.location.lat() ;
     latitude = gps.location.lng() ;
   ///////////////////////Location///////////
   Serial.println("  ");
   Serial.print("Longitude: ");
   Serial.println(longitude,8) ; //print latitude
   Serial.print("Latitude: ");
   Serial.println(latitude,8) ; //print longitude
   Serial.println("  ");
   ///////////////////////Date//////////////
   Serial.println("Date");
   Serial.print(gps.date.month());
   Serial.print("/");
   Serial.print(gps.date.day());
   Serial.print("/");
   Serial.print(gps.date.year());
   Serial.println("  ");
   ///////////////////////Time///////////
   Serial.println("Time: ");
   Serial.print(gps.time.hour());
   Serial.print(":");
   Serial.print(gps.time.minute());
   Serial.print(":");
   Serial.print(gps.time.second());
   Serial.println("  ");
   delay(1000);
   }
 }
}
