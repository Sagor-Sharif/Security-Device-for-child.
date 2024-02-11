//Sagor Sharif-01750467924
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial Gsm(8, 9);
char phone_no[] = "+8801750467924";
TinyGPS gps;
const int sms = A0;
const int call = A5;
int sms_state;
int call_state;
String textMessage;
void setup() {
  Serial.begin(9600);
  Gsm.begin(9600);
  Serial.print("AT+CMGF=1\r");
  delay(100);
  Serial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  pinMode(sms, INPUT_PULLUP);
  pinMode(call, INPUT_PULLUP);
}
 
void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (Serial.available()) {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c))
        newData = true;
    }
  }
  if (Gsm.available() > 0) {
    textMessage = Gsm.readString();
    textMessage.toUpperCase();
    delay(10);
  }
  Serial.println(failed);
  sms_state = digitalRead(sms);
 if (sms_state == LOW)
 {
   Serial.println("SMS Button Press:");
   float flat, flon;
   unsigned long age;
   gps.f_get_position(&flat, &flon, &age);
   Gsm.print("AT+CMGF=1\r");
   delay(400);
   Gsm.print("AT+CMGS=\"");
   Gsm.print(phone_no);
   Gsm.println("\"");
   Gsm.println("Alert I need help.............");
   Gsm.print("http://maps.google.com/maps?q=loc:");
   Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
   Gsm.print(",");
   Gsm.print(flon == TinyGPS ::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
   delay(200);
   Gsm.println((char)26);
   delay(200);
   Gsm.println();
   Serial.println("SMS Sent");
 }
 call_state = digitalRead(call);
 if(call_state == LOW)
 {
   Serial.println("Call Button Press:");
   Serial.println("Call");
   delay(1000);
   Gsm.println("ATD+8801750467924;");
   delay(50000);
   Gsm.println("ATH");
   delay(1000);
 
  } 
}
