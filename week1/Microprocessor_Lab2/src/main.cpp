#include <Arduino.h>
const int button1 = A0;
const int button2 = A1;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB = 0xFF;
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(button1)==LOW) count++;
  if(digitalRead(button2)==LOW) count--;
  if(count>7) count = 0;
  if(count<0) count = 7;
  if(count >= 0 && count < 6){
    PORTD = 0x04<<count;
    PORTB = 0x00;
    Serial.println("PORTD " + count);
  }else if(count >= 6 && count <= 7){
    PORTD = 0x00;
    PORTB = 0x01<<(count-6);
    Serial.println("PORTB" + count);
  }
  Serial.println(count);
  delay(200);
}