#include<Arduino.h>
const int pin1 = 10;
const int pin2 = 11;
int pin = 0;
char data;
String buff="";
char marker = 'N';
float brightness = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void loop(){
  if(Serial.available() > 0){
    data = Serial.read();
    buff += data;
    if(buff == "L1B"){
      pin = pin1;
      buff = ""; //clear storage
      Serial.println("pin1 is recv");
    }else if(buff == "L2B"){
      pin = pin2;
      buff = "";
    Serial.println("pin2 is recv");
    }
    if(data == marker){
      brightness = buff.toInt();
      Serial.println(brightness);
      analogWrite(pin, (brightness)*2.54);
      buff = "";
      pin = 0;
      delay(1000);
    }
  }
}

