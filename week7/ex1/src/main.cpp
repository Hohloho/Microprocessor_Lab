#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int btn1 = 2;
const int btn2 = 4;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10); //width, height
  // Display static text
  display.println("SW1");
  display.setCursor(0,44);
  display.println("SW2");
  display.drawCircle(64, 20, 10, WHITE);
  display.drawCircle(64, 50, 10, WHITE);
  display.display(); 
}

void sw1_On(){
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10); //width, height
  // Display static text
  display.println("SW1");
  display.setCursor(0,44);
  display.println("SW2");
  display.fillCircle(64, 20, 10, WHITE);
  display.drawCircle(64, 50, 10, WHITE);
  display.display(); 
  Serial.println("sw1 is On");
}

void sw2_On(){
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10); //width, height
  // Display static text
  display.println("SW1");
  display.setCursor(0,44);
  display.println("SW2");
  display.drawCircle(64, 20, 10, WHITE);
  display.fillCircle(64, 50, 10, WHITE);
  display.display(); 
  Serial.println("sw2 is On");
}

void OFF(){
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10); //width, height
  // Display static text
  display.println("SW1");
  display.setCursor(0,44);
  display.println("SW2");
  display.fillCircle(64, 20, 10, WHITE);
  display.fillCircle(64, 50, 10, WHITE);
  display.display(); 
  Serial.println("OFF");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btn1) == HIGH) sw1_On();
  if(digitalRead(btn2) == HIGH) sw2_On();
  if((digitalRead(btn1)==LOW)&&(digitalRead(btn2)==LOW)) OFF();
}