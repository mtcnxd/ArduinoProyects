#include <Arduino.h>

const char* ssid     = "Backup_CSL";
const char* password = "100%backup";
const char* host     = "mototools.esy.es"; // Your Raspberry
String path          = "/light.json";
const int pin        = LED_BUILTIN;

const int switchRightPin = 2;
const int switchLeftPin = 3;

const int outputPin = 4;
const int pilotPin = 5;

int toggle = 1;
