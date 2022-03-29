#include <Arduino.h>

const char* ssid     = "Backup_CSL";
const char* password = "100%backup";
const char* host     = "mototools.esy.es"; // Your Raspberry
const char* jsonObj  = "bulb";

const int httpsPort   = 80;

String path          = "/status/bulb.json";

const int switchRightPin = 0;
const int switchLeftPin = 14;
const int outputPin  = 13;

boolean canChange = true;
int toggle = 1;

int contador = 0;
