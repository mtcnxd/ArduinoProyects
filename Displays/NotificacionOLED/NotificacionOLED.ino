#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Definitions.h"
#include <idDHT11.h>

void dht_wrapper();
idDHT11 DHT11(DHTpin, DHTint, dht_wrapper);

void dht_wrapper() {
  DHT11.isrCallback();
}

void setup()   {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
}


void loop() {
  String val = String(getTemp());
  showLoader("Sensando...", 0, 15, 5);
  showChar("TEMP: " + val + " C", 5, 10);
  Serial.println(val);
  delay(5000);

  val = String(getHumi());
  showLoader("Sensando...", 0, 15, 15);
  showChar("HUMI: " + val + " %", 5, 10);
  Serial.println(val);
  delay(5000);
}

