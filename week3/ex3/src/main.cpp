#include <Arduino.h>
int clk_pin = 13;   //SHCP
int latch_pin = 10; //STCP
int data_pin = 11;  //DS
int button1 = 2;
int button2 = 3;
char read = 0;
byte num[] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
};

void setLed(uint8_t _state)
{
  digitalWrite(latch_pin, LOW);
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(data_pin, (_state >> (7 - i)) & 0x01);
    digitalWrite(clk_pin, HIGH);
    digitalWrite(clk_pin, LOW);
  }
  digitalWrite(latch_pin, HIGH);
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(clk_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.begin(9600);
}

int count = 0;

void loop()
{
  if (digitalRead(button1) == LOW)
  {
    count = count + 1;
    setLed(num[count]);
    delay(100);
  }
  else if (digitalRead(button2) == LOW)
  {
    count = count - 1;
    setLed(num[count]);
    delay(100);
  }
  if (count > 8)
    count = 0;
  if (count < 0)
    count = 8;
}