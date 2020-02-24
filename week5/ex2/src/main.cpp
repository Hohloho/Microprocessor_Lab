#include <Arduino.h>
#include <ThreeWire.h> 
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE 
RtcDS1302<ThreeWire> Rtc(myWire);
int ledPin = 13;

void printDateTime(const RtcDateTime& dt){ 
  Serial.print("Total minutes : ");
  Serial.print(dt.Minute(), DEC); 
  Serial.print(':'); 
  Serial.print(dt.Second(), DEC); 
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Rtc.Begin();
  RtcDateTime setting_time(0);
  Rtc.SetDateTime(setting_time); // set time to be like setting_time
  pinMode(ledPin, OUTPUT);
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  int second = now.Second();
  int minute = now.Minute();
  if (second==0 && minute==0) Serial.println("Start");
  if(second%2==0){
    digitalWrite(ledPin,HIGH);
  }else
  {
    digitalWrite(ledPin,LOW);
  }
  if(minute==2&&second==0) Serial.println("End");
  printDateTime(now);
  delay(1000);
  
}