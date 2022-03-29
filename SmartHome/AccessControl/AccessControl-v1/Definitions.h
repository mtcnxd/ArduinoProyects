#include <Arduino.h>

#define SS_PIN 10
#define RST_PIN 9

#define COMMON_ANODE
#ifdef COMMON_ANODE

#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif

#define redLed 7		// Set Led Pins
#define greenLed 6
#define blueLed 5

#define relay 4			// Set Relay Pin
#define wipeB 3			// Button pin for WipeMode

boolean match = false;          // initialize card match to false
boolean programMode = false;	// initialize programming mode to false

int successRead;		// Variable integer to keep if we have Successful Read from Reader

byte storedCard[4];		// Stores an ID read from EEPROM
byte readCard[4];		// Stores scanned ID read from RFID Module
byte masterCard[4];		// Stores master card's ID read from EEPROM

