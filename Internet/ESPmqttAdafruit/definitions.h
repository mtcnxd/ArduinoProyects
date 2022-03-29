#include <Arduino.h>

const char* ssid = "HOFFEN_IoT";
const char* password = "H0ffen.147";

const char* mqttServer = "io.adafruit.com";
const char* mqttUser = "mtcnxd";
const char* mqttPassword = "f0dd74b723d90a2ca81a2fc6af57c5e0dc6982e4";
const String mqttClientId = "mtc.nxd@gmail.com";

long lastMsg = 0;
char msg[50];
int value = 0;

int timeUpdate = 60000;
