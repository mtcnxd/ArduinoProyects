#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "definitions.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

ESP8266WiFiMulti WiFiMulti;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.begin(115200);
  setupWiFi();  
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setInsecure();

    HTTPClient https;

    for (int i = 0; i < 3; i++) {

      if (https.begin(*client, url + coin[i])) {
        int httpCode = https.GET();

        if (httpCode > 0) {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();

            // JSON Parse object
            const size_t capacity = 2 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 6 * JSON_OBJECT_SIZE(1) + 3 * JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(4) + 2 * JSON_OBJECT_SIZE(5) + 4 * JSON_OBJECT_SIZE(8) + 550;
            DynamicJsonDocument doc(capacity);

            DeserializationError error = deserializeJson(doc, payload);
            JsonObject obj = doc.as<JsonObject>();

            String book = obj["payload"]["book"];
            String last = obj["payload"]["last"];

            Serial.println(i);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Coin: " + book);
            lcd.setCursor(0, 1);
            lcd.print("Price: $ " + last);

          }
        } else {
          Serial.printf("GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }

        https.end();
      } else {
        Serial.printf("Unable to connect\n");
      }
      delay(timeUpdate);
    }

  }
}
