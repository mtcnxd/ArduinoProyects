#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

int pinRed = 5;
int pinGreen = 6;
int pinYellow = 4;
int pinOk = 13;

void setup() {
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinYellow, OUTPUT);

  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    char c = bluetooth.read();

    switch (c) {
      case 'Y':
        digitalWrite(pinRed, LOW);
        digitalWrite(pinYellow, HIGH);
        digitalWrite(pinGreen, LOW);
        bluetooth.println("Yellow");
        break;

      case 'G':
        digitalWrite(pinRed, LOW);
        digitalWrite(pinYellow, LOW);
        digitalWrite(pinGreen, HIGH);
        bluetooth.println("Green");
        break;

      case 'R':
        digitalWrite(pinRed, HIGH);
        digitalWrite(pinYellow, LOW);
        digitalWrite(pinGreen, LOW);
        bluetooth.println("Red");
        break;
    }

    digitalWrite(pinOk, HIGH);
    delay(200);
    digitalWrite(pinOk, LOW);
  }
}
