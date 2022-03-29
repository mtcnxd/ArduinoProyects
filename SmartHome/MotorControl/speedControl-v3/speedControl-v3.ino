#include <TimerOne.h>
#include "Definitions.h"

void setup() {
  pinMode(AC_pin, OUTPUT);
  attachInterrupt(1, zero_cross_detect, FALLING);
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(dim_check, freqStep);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    char value = Serial.read();
    changeSpeed(value);
  }
  delay(50);
  Serial.println(dim);
}
