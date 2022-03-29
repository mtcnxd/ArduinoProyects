#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "Definitions.h"

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(switchRightPin, INPUT_PULLUP);
  pinMode(switchLeftPin, INPUT_PULLUP);
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("OK");
  Serial.println("IP address: " + WiFi.localIP());
}

void loop(void) {
  sendServer("Humedad", contador);
  contador++;

  delay (5000);
}
