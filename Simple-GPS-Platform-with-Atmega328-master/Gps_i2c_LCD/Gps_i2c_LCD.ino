#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
   lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing");
  delay(2000);
}
void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
{ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LAT:");
  lcd.setCursor(5,0);
  lcd.print(gps.location.lat(), 6);
  lcd.setCursor(0,1);
  lcd.print("LONG:");
  lcd.setCursor(5,1);
  lcd.print(gps.location.lng(), 6);
  delay(1000);
  }
  else
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wait'n 4 GPS fix");
  delay(4000);
  }

  //Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Date:");
  lcd.setCursor(0,1);
  lcd.print(gps.date.month());
  lcd.setCursor(2,1);
  lcd.print("/");
  lcd.setCursor(3,1);
  lcd.print(gps.date.day());
  lcd.setCursor(5,1);
  lcd.print("/");
  lcd.print(gps.date.year());
   delay(1000);
  }
  else
  {   lcd.clear();
      lcd.setCursor(0,0);   
      lcd.print("INVALID");
      delay(4000);
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    //if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time: ");
    lcd.setCursor(0,1);
    lcd.print(gps.time.hour());
    lcd.setCursor(2,1);
    lcd.print(":");
    
    //if (gps.time.minute() < 10) lcd.print("0");
    lcd.setCursor(3,1);
    lcd.print(gps.time.minute());
      
   // if (gps.time.second() < 10) lcd.print("0");
    
    lcd.setCursor(5,1);
    lcd.print(":");
    lcd.setCursor(6,1);
    lcd.print(gps.time.second());
    delay(1000);
  }
  else
  {
    lcd.print("INVALID");
  }
}
