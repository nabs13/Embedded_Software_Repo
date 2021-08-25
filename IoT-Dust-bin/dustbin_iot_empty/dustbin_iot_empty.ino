// Select your modem:
#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <ThingerTinyGSM.h>

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(3, 2); // RX, TX
#endif

#define USERNAME " "
#define DEVICE_ID " "
#define DEVICE_CREDENTIAL " "

// use your own APN config
#define APN_NAME " "
#define APN_USER " "
#define APN_PSWD " "
#define CARD_PIN ""

ThingerTinyGSM thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL, Serial1);
#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() {

  Serial1.begin(57600);

  thing.setAPN(APN_NAME, APN_USER, APN_PSWD);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  thing["SONIC"] >> [] (pson& out){
      double duration, distance;
      digitalWrite(TRIGGER_PIN, LOW);  // Get Start
      delayMicroseconds(2); // stable the line 
      digitalWrite(TRIGGER_PIN, HIGH); // sending 10 us pulse
      delayMicroseconds(10); // delay 
      digitalWrite(TRIGGER_PIN, LOW); // after sending pulse wating to receive signals 
      duration = pulseIn(ECHO_PIN, HIGH); // calculating time 
      distance = (duration/2) / 29.1; // single path 
      out = distance;
  };

}

void loop() {
  
thing.handle();
}
