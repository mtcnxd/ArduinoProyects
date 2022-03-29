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
  if (digitalRead(switchRightPin) == HIGH) {
    if (digitalRead(switchLeftPin) == LOW) {
      if (canChange) {
        canChange = false;
        sendServer("bulb");
      }
    }
  } else if (digitalRead(switchRightPin) == LOW) {
    if (digitalRead(switchLeftPin) == HIGH) {
      if (!canChange) {
        canChange = true;
        sendServer("bulb");
      }
    }
  }

  getServer();
}
