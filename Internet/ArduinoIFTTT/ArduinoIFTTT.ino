#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "definitions.h"

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  setupWiFi();
}

void loop() {
  if (contador > 100) {
    launch_ifttt(EVENT_NAME);
    contador = 0;
  }

  Serial.println (contador);
  contador ++;
  delay(2000);
}
