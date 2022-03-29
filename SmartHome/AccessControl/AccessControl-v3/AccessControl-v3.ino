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

  //Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  if (digitalRead(wipeB) == LOW) {
    digitalWrite(redLed, HIGH);
    //Serial.println(F("Wipe Button Pressed"));
    //Serial.println(F("You have 5 seconds to Cancel"));
    //Serial.println(F("This will be remove all records and cannot be undone"));

    delay(5000);
    if (digitalRead(wipeB) == LOW) {
      //Serial.println(F("Starting Wiping EEPROM"));
      for (int x = 0; x < EEPROM.length(); x = x + 1) {
        if (EEPROM.read(x) == 0) {
          // do nothing, already clear, go to the next address in order to save time and reduce writes to EEPROM
        }
        else {
          EEPROM.write(x, 0);
        }
      }
      //Serial.println(F("EEPROM Successfully Wiped"));
    }
    else {
      //Serial.println(F("Wiping Cancelled"));
    }
  }

  if (EEPROM.read(1) != 143) {
    //Serial.println(F("No Master Card Defined"));
    //Serial.println(F("Scan A Tag to Define as Master Card"));
    do {
      successRead = getID();
    }
    while (!successRead);

    for ( int j = 0; j < 4; j++ ) {
      EEPROM.write( 2 + j, readCard[j] );
    }
    EEPROM.write(1, 143);
    //Serial.println(F("Master Card Defined"));
  }
  //Serial.println(F("-------------------"));
  //Serial.println(F("Master Card's UID"));
  for ( int i = 0; i < 4; i++ ) {
    masterCard[i] = EEPROM.read(2 + i);
    //Serial.print(masterCard[i], HEX);
  }
  //Serial.println("");
  //Serial.println(F("-------------------"));
  //Serial.println(F("Everything Ready"));
  //Serial.println(F("Waiting Tags to be scanned"));
}

void loop () {
  do {
    successRead = getID();
  }
  while (!successRead);
  if (programMode) {
    if ( isMaster(readCard) ) {
      //Serial.println(F("Master Card Scanned"));
      //Serial.println(F("Exiting Program Mode"));
      //Serial.println(F("-----------------------------"));
      programMode = false;
      digitalWrite(redLed, LOW);
      return;
    }
    else {
      if ( findID(readCard) ) {
        //Serial.println(F("I know this Tag, removing..."));
        deleteID(readCard);
        readConfirm();
        //Serial.println("-----------------------------");
      }
      else {
        //Serial.println(F("I do not know this Tag, adding..."));
        writeID(readCard);
        readConfirm();
        //Serial.println(F("-----------------------------"));
      }
    }
  }
  else {
    if ( isMaster(readCard) ) {
      programMode = true;
      //Serial.println(F("Hello Master - Entered Program Mode"));
      int count = EEPROM.read(0);
      //Serial.print(F("I have "));
      //Serial.print(count);
      //Serial.print(F(" record(s) on EEPROM"));
      //Serial.println("");
      //Serial.println(F("Scan a Tag to ADD or REMOVE"));
      //Serial.println(F("-----------------------------"));
      digitalWrite(redLed, HIGH);      
    }
    else {
      if ( findID(readCard) ) {
        //Serial.println(F("Welcome, you have access"));
        granted();
      }
      else {
        //Serial.println(F("Good Bye, report this error to admin"));
        denied();
      }
    }
  }
}
