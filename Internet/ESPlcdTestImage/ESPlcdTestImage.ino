#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "definitions.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 2);

void setup()   {
  display.begin();
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
}


void loop() {
  Serial.println("LCD");
  display.clearDisplay();
  display.drawBitmap(5, 20, termometer, 8, 8, BLACK);
  display.drawBitmap(25, 20, happy, 8, 8, BLACK);
  display.drawBitmap(40, 20, bateria, 8, 8, BLACK);  

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Hello, world!");
  
  display.display();
  delay(1000);
}
