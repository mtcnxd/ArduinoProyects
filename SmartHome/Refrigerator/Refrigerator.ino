#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "definitions.h"

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  checkOn();
  sensors.begin();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  delay(500);
}

void loop() {
  currentMillis = millis();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //###### Si el tiempo transcurrido es mayor a 60 segundos #####//
  
  if (currentMillis - previousMillis >= interval) {  
    previousMillis = currentMillis;
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    snprintf (temp, 10, "%ld", temperature);
    client.publish("mtcnxd/feeds/temperature", temp);

    showInfoSerial();

    //###### Si la temperatura es mayor al setpoint #####//

    if (temperature > setpoint && coolingMode == true) {
      cooling();
      snprintf (mins, 10, "%ld", runningTimer);
      client.publish("mtcnxd/feeds/time", mins);
      runningTimer++;
    } else {
      waiting();
      waitForRun();
    }
  }
}
