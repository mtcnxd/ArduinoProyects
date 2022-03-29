#include <Arduino.h>

const char* ssid     = "Backup_CSL";
const char* password = "100%backup";
const char* host     = "mototools.esy.es"; // Your Raspberry
const int httpsPort   = 80;

String path          = "/status/light.json";

const int switchRightPin = 0;
const int switchLeftPin = 14;
const int outputPin  = LED_BUILTIN;

boolean canChange = true;
int toggle = 1;
