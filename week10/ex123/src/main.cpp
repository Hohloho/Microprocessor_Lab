#include<Arduino.h>
#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 9

#define EN_A 2
#define EN_B 3

bool curA = 0; 
bool curB = 0; 
bool preA = 0; 
bool preB = 0; 

void check_dir(bool dir){
  static int count = 0;
  if(dir) {
    count++;
    Serial.println("Count = " + String(count) + " Direction: clockwise");
  }
  else {
    count--;
    Serial.println("Count = " + String(count) + " Direction: counter-clockwise");
  }
}

void check_value(){
    curA = !digitalRead(EN_A);
    curB = !digitalRead(EN_B);
    if(curA && curB){
        if((preA == 1) && (preB == 0)) check_dir(1);
        else if((preA == 0) && (preB == 1)) check_dir(0);
    }
  
    preA = curA;
    preB = curB;
}

void setup(){
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(EN_A, INPUT_PULLUP);
  pinMode(EN_B, INPUT_PULLUP);
 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(EN_A), check_value, FALLING);
   attachInterrupt(digitalPinToInterrupt(EN_B), check_value, FALLING);
}

void speed(int speed){
  if((0<=speed) && (speed<=255)){
    digitalWrite(MOTOR_D1_PIN, HIGH);
    digitalWrite(MOTOR_D2_PIN, LOW);
    analogWrite(MOTOR_PWM_PIN, speed);
  }else if((-255<=speed) && (speed<0)){
    digitalWrite(MOTOR_D1_PIN, LOW);
    digitalWrite(MOTOR_D2_PIN, HIGH);
    analogWrite(MOTOR_PWM_PIN, -speed);
  }
}

void loop(){
  speed(200);
  delay(100);
}