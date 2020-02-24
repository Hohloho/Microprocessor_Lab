#include <Arduino.h>
int second = 0;
int min = 0;
int ledPin = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(second==0 && min==0) Serial.println("Start");
  Serial.println("Total minutes : ");
  Serial.println(min);
  Serial.println("Total seconds : ");
  Serial.println(second);
  if(second==0 && min==0) Serial.println("Start");
  if(second%2==0){
    digitalWrite(ledPin,HIGH);
  }else
  {
    digitalWrite(ledPin,LOW);
  }
  if(min==2&&second==0) Serial.println("End");
  delay(1000);
  if(second==60){
    min++; 
    second=0;
  }
  second++;
  delay(1000);
}