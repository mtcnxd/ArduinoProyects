#include<FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 5
#define CLOCK_PIN 4

CRGB leds[NUM_LEDS];

int inChar;

void setup() {
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}


String cadena = "";     //  Aqui Guardamos los datos
int intensidad = 0;     //  Este es valor a mandar por PWM
int color = 0;          //  Bandera para saber que color modificar

void loop() {
  if (Serial.available() > 0) {
    inChar = Serial.read();
  }

  if (isDigit(inChar)) {
    cadena += (char)inChar;
  }  else  {
    Serial.println(inChar);
    switch (inChar) {
      case 'R':
        color = 'R';
        break;
      case 'G':
        color = 'G';
        break;
      case 'B':
        color = 'B';
        break;
    }
  }

  if (inChar == '\n') {
    intensidad = cadena.toInt();
    intensidad = map(intensidad, 0, 100, 0, 255);

    dimColor(intensidad, color);        // escribimos en el puerto el valor de la intensidad
    cadena = "";                            // Vaciamos los valores
  }

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
