#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "definitions.h"

WiFiUDP loxone;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  Serial.print("Connecting ...");
  WiFi.begin("OFICINA", "2627F68597");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  loxone.begin(port);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (sensorValue <= 0) {
      sensorValue = 100;
    } else {
      sensorValue = sensorValue - 1;
    }

    Serial.printf("%i %\n\r", sensorValue);
    enviarDatos(sensorValue);

    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
  }
}
