#include <Arduino.h>

#define SS_PIN 10
#define RST_PIN A3

#define redLed 9
#define speaker 8

#define relay 4
#define wipeB 3

boolean match = false;
boolean programMode = false;

int successRead;

byte storedCard[4];
byte readCard[4];
byte masterCard[4];

