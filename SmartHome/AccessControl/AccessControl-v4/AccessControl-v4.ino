#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include "Definitions.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  pinMode(speaker, OUTPUT);    
  pinMode(redLed, OUTPUT);
  pinMode(relay, OUTPUT);  
  pinMode(wipeB, INPUT_PULLUP);

  digitalWrite(relay, LOW);
  digitalWrite(redLed, LOW);

  SPI.begin();
  mfrc522.PCD_Init();

  if (digitalRead(wipeB) == LOW) {
    digitalWrite(redLed, HIGH);

    delay(5000);
    if (digitalRead(wipeB) == LOW) {
      for (int x = 0; x < EEPROM.length(); x = x + 1) {
        if (EEPROM.read(x) == 0) {
        }
        else {
          EEPROM.write(x, 0);
        }
      }
    }
    else {
    }
  }

  if (EEPROM.read(1) != 143) {
    do {
      successRead = getID();
    }
    while (!successRead);

    for ( int j = 0; j < 4; j++ ) {
      EEPROM.write( 2 + j, readCard[j] );
    }
    EEPROM.write(1, 143);
  }
  for ( int i = 0; i < 4; i++ ) {
    masterCard[i] = EEPROM.read(2 + i);
  }
}

void loop () {
  do {
    successRead = getID();
  }
  while (!successRead);
  if (programMode) {
    if ( isMaster(readCard) ) {
      programMode = false;
      digitalWrite(redLed, LOW);
      return;
    }
    else {
      if ( findID(readCard) ) {
        deleteID(readCard);
        readConfirm();
      }
      else {
        writeID(readCard);
        readConfirm();
      }
    }
  }
  else {
    if ( isMaster(readCard) ) {
      programMode = true;
      int count = EEPROM.read(0);
      digitalWrite(redLed, HIGH);      
    }
    else {
      if ( findID(readCard) ) {
        granted();
      }
      else {
        denied();
      }
    }
  }
}
