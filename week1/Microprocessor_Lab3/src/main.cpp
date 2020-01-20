#include <Arduino.h>
const int button1 = A0;
const int button2 = A1;
const int potent = A2;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB = 0xFF;
  Serial.begin(9600);
}

bool forward = true;

void loop() {
  if(digitalRead(button1)==LOW) forward = true; //count++;
  if(digitalRead(button2)==LOW) forward = false;
  if(forward == true){
    count++;
  }else{
    count--;
  }
  if(count>7) count = 0;
  if(count<0) count = 7;
  if(count >= 0 && count < 6){
    PORTD = 0x04<<count;
    PORTB = 0x00;
  }else if(count >= 6 && count <= 7){
    PORTD = 0x00;
    PORTB = 0x01<<(count-6);
  }
  Serial.println(count);
  delay(analogRead(potent));
}
