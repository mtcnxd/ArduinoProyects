#include <Arduino.h>

const char* ssid = "SMARTHOME";
const char* password = "100%smart";

const char* mqttServer = "io.adafruit.com";
const char* mqttUser = "mtcnxd";
const char* mqttPassword = "f0dd74b723d90a2ca81a2fc6af57c5e0dc6982e4";
const String mqttClientId = "arduinoClient";

const int ledPin =  LED_BUILTIN;
const int defrostPin = 0;
const int oneWireBus = 4;
const int motorPin = 5;


int setpoint = 13;
int temperature = 0;
int runningTimer = 0;
int waitingTimer = 0;
int sleepTimer = 35;  // 35 minutos

const long interval = 60000;   // 60 segundos
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long previous = 0;

boolean coolingMode = true;
boolean ecoMode = false;

char temp[10];
char mins[10];

// Si el tiempo de enfriamiento es mayor a 30 mins 
// encender automaticamente el modo defrost
