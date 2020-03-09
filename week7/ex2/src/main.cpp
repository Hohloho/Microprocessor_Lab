#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ThreeWire.h> 
#include <RtcDS1302.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
ThreeWire myWire(4,5,2); // IO, SCLK, CE 
RtcDS1302<ThreeWire> Rtc(myWire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printDateTime(const RtcDateTime& dt){ 
  display.setTextSize(1);
	display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print(dt.Year(), DEC);
  display.print(':'); 
  display.print(dt.Month(), DEC);
  display.print(':'); 
  display.print(dt.Day(), DEC);
  display.print(':'); 
  display.print(dt.Minute(), DEC); 
  display.print(':'); 
  display.print(dt.Second(), DEC); 
  display.display();
}


void setup() {
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
	RtcDateTime now = Rtc.GetDateTime();
	display.setCursor(0,0);
	printDateTime(now);
	display.display();
	delay(1000);
}