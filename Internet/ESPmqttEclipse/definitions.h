#include <Arduino.h>

const char* ssid = "HOFFEN_IoT";
const char* password = "H0ffen.147";

const char* mqttServer = "mqtt.eclipse.org";
const char* mqttUser = "";
const char* mqttPassword = "";
const String mqttClientId = "";

long lastMsg = 0;
char msg[50];
int value = 0;

int timeUpdate = 1000;
