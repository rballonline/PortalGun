#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <Adafruit_NeoPixel.h>
#include "Timer.h"
#define NUMPIXELS     10
#define PIN            3

Timer t;

const int triggerPin = 2;
int potPin = 2;
int brightnessPin = 3;
int potValue = 0;
int triggerValue = 0;

boolean triggerDown = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(4800);
  Serial.println("setup");

  int brightnessEvent = t.every(1, checkBrightness);
  int triggerEvent = t.every(1, checkTrigger);
  int changePlasmaEvent = t.every(50, changePlasma);
  int changeFrontEvent = t.every(10, changeFront);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Portal Gun v1.2"); 
  lcd.setCursor(0, 1);
  lcd.print("Initializing"); 
  
  pixels.begin(); // This initializes the NeoPixel library.
  resetPixels();
}

void changeFront() {
    if(button
    for(int x = 6; x < 9; x++) {
      pixels.setPixelColor(x,0,255, 0);
    }
    pixels.show();
  }
   
  if(random(0, 1000) < 50) {
    for(int x = 6; x < 9; x++) {
      int g1 = g-random(0,50);
      pixels.setPixelColor(x,0,g1, 0);
    }
    pixels.show();
  }
}

void checkBrightness() { 
  int brightnessValue = analogRead(brightnessPin);
  /*Serial.print("brightnessValue==== ");
  Serial.println(brightnessValue);*/
  
  int brightness = map(brightnessValue, 0, 1000, 0, 200);
  pixels.setBrightness(brightness);
  pixels.show();
}

void checkTrigger() {  
  triggerValue = digitalRead(triggerPin);
  Serial.print("triggerValue============== ");
  Serial.println(triggerValue);
  if(triggerValue ==  1) {
    triggerDown = true;
  } else {
    triggerDown = false;
  }
}

void changePlasma() {  
  triggerValue = digitalRead(triggerPin);
  
  int g = 225;
  int r = 40;
  int b = 40;

  pixels.setPixelColor(0,0,255,0);  
  for(int x = 1; x < 6; x++) {
    int change = random(0,40);
    int r1 = r-change;
    int g1 = g-random(0,100);
    int b1 = b-change;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    pixels.setPixelColor(x,r1,g1, b1);
  }
}

void loop() {
  t.update();
  potValue = analogRead(potPin);
  Serial.print("potValue: ");
  Serial.println(potValue);

  if(potValue > 750) {
    lcd.setCursor(0, 1);
    lcd.print("Get Shwifty     "); 
  } else if(potValue > 500 && potValue < 750) {
    lcd.setCursor(0, 1);
    lcd.print("Wubba lubba dub"); 
  } else if(potValue > 250 && potValue < 501) {
    lcd.setCursor(0, 1);
    lcd.print("That's Hot!     "); 
  } else if(potValue > 0 && potValue < 251) {
    lcd.setCursor(0, 1);
    lcd.print("Poopybutthole"); 
  }

}

void resetPixels() {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

