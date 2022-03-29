#include <Arduino.h>

#define SS_PIN 10
#define RST_PIN 9

#define speaker 8
#define redLed 7

#define relay 4
#define wipeB 3

boolean match = false;          // initialize card match to false
boolean programMode = false;	// initialize programming mode to false

int successRead;		// Variable integer to keep if we have Successful Read from Reader

byte storedCard[4];		// Stores an ID read from EEPROM
byte readCard[4];		// Stores scanned ID read from RFID Module
byte masterCard[4];		// Stores master card's ID read from EEPROM

