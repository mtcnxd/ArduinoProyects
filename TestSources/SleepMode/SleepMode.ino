#include "LowPower.h"
int LED = 13 ;

void setup() {
  pinMode(13, OUTPUT);
}


void loop() {
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
}
