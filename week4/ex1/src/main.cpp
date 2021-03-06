#include <SPI.h>
#include <arduino.h>
const int DATA = 11;
const int CLK = 13;
const int SS = 10;
const int SS_2 = 9;
const int leftPin = 2;
const int rightPin = 3;
const int sPin = 4;
const int buzzer = 5;

bool count = false;

int counter = 10;

int number[10] = {
  0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};

void spi_1(int data){
  SPI.transfer(data); 
  digitalWrite(SS,HIGH); 
  digitalWrite(SS,LOW);
  delay(200);
}

void spi_2(int data){
  SPI.transfer(data); 
  digitalWrite(SS_2,HIGH); 
  digitalWrite(SS_2,LOW);
  delay(200);
}

void setup(){
  SPI.begin();
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  pinMode(SS,OUTPUT);
  pinMode(SS_2,OUTPUT);
  pinMode(leftPin,INPUT);
  pinMode(rightPin,INPUT);
  pinMode(sPin,INPUT);
  Serial.begin(9600);

}

void loop(){
  int left = digitalRead(leftPin);
  int right = digitalRead(rightPin);
  int readS = digitalRead(sPin);

  spi_2(number[counter%10]);
  spi_1(number[counter/10]);

  if (counter == 100) counter = 0;
  if (right == LOW) counter++ ;
  if (left == LOW) counter-- ;
  if (readS == LOW && count==false) count = true;
  while(count && (counter >= 0)){
    readS = digitalRead(sPin);
    counter--;
    spi_2(number[counter%10]);
    spi_1(number[counter/10]);
    delay(200);
    if(readS == LOW && count) count = false;
    if(counter==0){
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      count = false;
    }
  }
  delay(200);
}