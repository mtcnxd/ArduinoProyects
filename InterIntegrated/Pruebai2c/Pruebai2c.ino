#include <Wire.h>
int data = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(0x04);
  Wire.onReceive(sensado);
}

void loop() {
}

void sensado (int data) {
  int x = Wire.read();
  Serial.println(x);
}

