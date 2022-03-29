#include <Arduino.h>

const char* ssid = "HOFFEN_IoT";
const char* password = "H0ffen.147";

const char* mqttServer = "postman.cloudmqtt.com";
const char* mqttUser = "rntpgoyp";
const char* mqttPassword = "XYAbxyUROeeP";
const String mqttClientId = "mtc.nxd@gmail.com";

long lastMsg = 0;
char msg[50];
int value = 0;

int timeUpdate = 1000;
