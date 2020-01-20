#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB = 0xFF;
}

void loop() {
  for(int i = 0; i<=6; ++i)
  {
    PORTD = 0x04<<i;
    if(i==6)
    {
      PORTD = 0x00; //0b0000 0100
      for(int i = 0;i<=2;++i)
      {
        PORTB = 0x01<<i; //0b0000 0001
        delay(200);
      }
    }
    delay(200);
  }
}