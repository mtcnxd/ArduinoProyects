#include <Arduino.h>

const int ledPin = 13;
const int ledPwm = 3;
const int interval = 300;

long anterior = 0;
int sensorPin = 0;

int pwmValue = 0;

String cadena = "";

char valueRead;
