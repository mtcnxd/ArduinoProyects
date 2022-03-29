#include <SoftwareSerial.h>
#include "Definitions.h"

SoftwareSerial bluetooth(10, 11);

void setup() {
  pinMode (ledPin, OUTPUT);
  pinMode (ledPwm, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  long actual = millis();

  if (actual - anterior >= interval) {
    bluetooth.println(sensorPin);
    Serial.println(sensorPin);
    anterior = actual;
    sensorPin++;
  }

  if (bluetooth.available()) {
    valueRead = bluetooth.read();

    if (isDigit(valueRead)) {
      cadena += (char)valueRead;
    } else {
      changeState(valueRead);
    }

    if (valueRead == '\n') {
      pwmValue = cadena.toInt();
      changeDimmer (pwmValue);
      cadena = "";
    }
  }
}
