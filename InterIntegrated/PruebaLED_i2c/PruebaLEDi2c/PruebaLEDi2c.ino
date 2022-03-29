#include <Wire.h>
int data = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(4);
}

void loop() {
  while(Wire.available()) {
    Serial.print ("Data is: ");
    data = Wire.read();
    Serial.println (data);
  }
}
