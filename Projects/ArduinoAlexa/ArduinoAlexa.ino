#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

boolean connectWifi();

void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

const char* ssid = "SMARTHOME";
const char* password = "100%smart";
boolean wifiConnected = false;

Espalexa espalexa;
EspalexaDevice* device3;

void setup() {
  Serial.begin(115200);
  wifiConnected = connectWifi();

  if (wifiConnected) {
    //simplest definition, default state off
    espalexa.addDevice("Led 1", firstLightChanged);
    //third parameter is beginning state (here fully on)
    espalexa.addDevice("Led 2", secondLightChanged, 255);

    //you can also create the Device objects yourself like here
    device3 = new EspalexaDevice("Led 3", thirdLightChanged);
    espalexa.addDevice(device3); //and then add them
    device3->setValue(128); //this allows you to e.g. update their state value at any time!
    espalexa.begin();

  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop() {
  espalexa.loop();
  delay(1);
}
