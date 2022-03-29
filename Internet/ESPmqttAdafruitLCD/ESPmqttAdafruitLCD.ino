#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "definitions.h"

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 2);

void setup() {
  display.begin();
  display.setContrast(80);
  
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setupWiFi();
    
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  
  if (now - lastMsg > timeUpdate) {
    lastMsg = now;
    value = analogRead(A0);
    snprintf (msg, 50, "%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("mtcnxd/feeds/sensor", msg);
  }
}
