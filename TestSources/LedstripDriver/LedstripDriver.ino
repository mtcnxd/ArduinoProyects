#include<FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 5
#define CLOCK_PIN 4

CRGB leds[NUM_LEDS];

int brightness = 1;
int fadeAmount = 1;

void setup() {
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  leds[0].setRGB(10, 10, 0);
  FastLED.show();
  delay(10);

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  brightness = brightness + fadeAmount;

  Serial.println(brightness);
}


void dimColor(int brightness, char color) {
  switch (color) {
    case 'R':
      leds[0].setRGB(brightness, 0, 0);
      FastLED.show();
      break;
    case 'G':
      leds[0].setRGB(0, brightness, 0);
      FastLED.show();
      break;
    case 'B':
      leds[0].setRGB(0, 0, brightness);
      FastLED.show();
      break;
  }
}
