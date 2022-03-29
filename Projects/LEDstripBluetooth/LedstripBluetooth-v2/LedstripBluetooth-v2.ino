#include <SoftwareSerial.h>
#include<FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 5
#define CLOCK_PIN 4

CRGB leds[NUM_LEDS];
SoftwareSerial bluetooth(9, 8);

char valueRead;
String cadena = "";
int rojo, verde, azul;

void setup() {
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
  bluetooth.begin(9600);

  leds[0].setRGB(30, 30, 30);
  FastLED.show();
}

void loop() {
  if (bluetooth.available()) {
    valueRead = bluetooth.read(); // = 63R76G36B

    if (isDigit(valueRead)) {
      cadena += (char)valueRead;
    }
    if (valueRead == 'R') {
      rojo = cadena.toInt();
      cadena = "";
    }

    if (valueRead == 'G') {
      verde = cadena.toInt();
      cadena = "";
    }

    if (valueRead == 'B') {
      azul = cadena.toInt();
      cadena = "";
    }

    changeColor(rojo, verde, azul);
  }
}

void changeColor (int Red, int Green, int Blue) {
  leds[0].setRGB(Red, Green, Blue);
  FastLED.show();
}
