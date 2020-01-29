#include <Arduino.h>
int clk_pin = 13;   //SHCP
int latch_pin = 10; //STCP
int data_pin = 11;  //DS

void setup()
{
  // put your setup code here, to run once:
  pinMode(clk_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  Serial.begin(9600);
}

void setLed(uint16_t newdata)
{
  digitalWrite(latch_pin, LOW);
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(data_pin, (newdata >> (15 - i)) & 0x01);
    digitalWrite(clk_pin, HIGH);
    digitalWrite(clk_pin, LOW);
  }
  digitalWrite(latch_pin, HIGH);
  delay(100);
}

int counter = 0;

void loop()
{
  setLed(0x01 << counter);
  if (counter > 15)
    counter = 0;
  counter++;
}
