#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SSD1306Wire.h"
#include "definitions.h"

SSD1306Wire display(0x3c, 5, 4);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println();
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  setupWiFi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(100);
}
