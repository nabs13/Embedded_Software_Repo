#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

  
  float tempC;
  int reading;
  int tempPin = A1;
  
void setup() {
 
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  float average = 0.00;
  int light_int = analogRead(A2); //LDR assignment
  
  int sensorValue = analogRead(A0);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (56.40 / 1023.0);

  
  
  lcd.print("Voltage/v");
  lcd.setCursor(11,0);
  lcd.print(voltage);
 
  
//delay(1000);

 //for(int i = 0; i < 1000; i++) {
        average = average + (.066 * analogRead(A3)-67.49);//resolution of the Current sensor;
        
        
   //     delay(1);
             
  //}
  //delay(2000);
  lcd.setCursor(0,1);
  lcd.print("current/mA");
  lcd.setCursor(11,1);
  lcd.print(average);
  delay(3500);
  lcd.clear();
 
  delay(1000);
  lcd.print("Wattage/mW");
  lcd.setCursor(11,0);
  lcd.print(average * voltage);
  delay(3000);
  lcd.clear();

  analogReference(INTERNAL);
  reading = analogRead(tempPin);
  tempC = reading / 9.31;// Temperature sensor calibration
  
  delay(1000);
  lcd.print("Temp/deg");
  lcd.setCursor(10,0);
  lcd.print(tempC);
//  lcd.clear();

  if (light_int > 900)
  {
    lcd.setCursor(0,1);
    lcd.print("Light Int: ");
  lcd.setCursor(11,1);
  lcd.print("HIGH");
    } else {
      lcd.setCursor(0,1);
    lcd.print("Light Int: ");
  lcd.setCursor(11,1);
  lcd.print("LOW");
      
      }
  delay(3500);
  lcd.clear();

}
