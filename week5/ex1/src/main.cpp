#include <Arduino.h>
#include <ThreeWire.h> 
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE 
RtcDS1302<ThreeWire> Rtc(myWire);
int ledPin = 13;
byte prevSec = 0;

void printDateTime(const RtcDateTime& dt){ 
  // Serial.print(dt.Year(), DEC);
  // Serial.print('/');
  // Serial.print(dt.Month(), DEC); 
  // Serial.print('/');
  // Serial.print(dt.Day(), DEC); 
  // Serial.print(' '); 
  // Serial.print(dt.Hour(), DEC); 
  // Serial.print(':'); 
  Serial.print("Total minutes : ");
  Serial.print(dt.Minute(), DEC); 
  Serial.print(':'); 
  Serial.print(dt.Second(), DEC); 
  Serial.println();
  // Serial.print("Total Seconds since 1/1/2000 : "); 
  // Serial.print(dt.TotalSeconds());
  // Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Rtc.Begin();
  RtcDateTime setting_time(0);
  // // year, month, dayOfMonth, hour, minute, second
  // printDateTime(setting_time);
  //Try to comment This line
  Rtc.SetDateTime(setting_time); // set time to be like setting_time
  pinMode(ledPin, OUTPUT);
}


void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  int second = now.Second();
  if(second%2==0){
    digitalWrite(ledPin,HIGH);
  }else
  {
    digitalWrite(ledPin,LOW);
  }
  // put your main code here, to run repeatedly:
  delay(1000);
}