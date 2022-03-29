#include <SoftwareSerial.h>
#include<FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 5
#define CLOCK_PIN 4

CRGB leds[NUM_LEDS];
SoftwareSerial bluetooth(9, 8);

char valueRead;
String cadena = "";
int color = 0;
int valueSet, Red, Green, Blue;

void setup() {
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    valueRead = bluetooth.read();
    //Serial.println(valueRead);

    if (isDigit(valueRead)) {
      cadena += (char)valueRead;
    } else {
      switch (valueRead) {
        case 'R':
          color = 1;
          break;
        case 'G':
          color = 2;
          break;
        case 'B':
          color = 3;
          break;
      }
    }

    if (valueRead == '\n') {
      valueSet = cadena.toInt();

      switch (color) {
        case 1:
          Red = valueSet;
          changeColor(Red, Green, Blue);
          break;
        case 2:
          Green = valueSet;
          changeColor(Red, Green, Blue);
          break;
        case 3:
          Blue = valueSet;
          changeColor(Red, Green, Blue);
          break;
      }
      cadena = "";
    }
  }
}

void changeColor (int Red, int Green, int Blue) {
  Serial.print(Red);
  Serial.print(Green);
  Serial.print(Blue);
  Serial.println();
  leds[0].setRGB(Red, Green, Blue);
  FastLED.show();
}
