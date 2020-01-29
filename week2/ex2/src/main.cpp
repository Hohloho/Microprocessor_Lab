#include <Arduino.h>
const int clk_pin = 13;   //SHCP
const int latch_pin = 10; //STCP
const int data_pin = 11;  //DS
const int button1 = 2;
const int button2 = 3;

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

int count = 0;
bool forward = true;

void loop()
{
  if (digitalRead(button1) == LOW)
    count++;
  if (digitalRead(button2) == LOW)
    count--;
  setLed(0x01 << count);
  if (count > 15)
    count = 0;
  if (count < 0)
    count = 15;
}

//write the program to illuminate LED seperately and use the push switch to select the led for illumination
//what problem did you face and what are its solution