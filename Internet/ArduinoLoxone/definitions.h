#include <Arduino.h>

const int ledPin = LED_BUILTIN;

const char* host = "192.168.100.228";

const uint16_t port = 1234;

const long interval = 30000;

unsigned long previousMillis = 0; 

int sensorValue = 100;
