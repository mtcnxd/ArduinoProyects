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

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  //Wipe Code if Button Pressed while setup run (powered on) it wipes EEPROM
  if (digitalRead(wipeB) == LOW) {	// when button pressed pin should get low, button connected to ground
    digitalWrite(redLed, HIGH);	// Red Led stays on to inform user we are going to wipe
    Serial.println(F("Wipe Button Pressed"));
    Serial.println(F("You have 5 seconds to Cancel"));
    Serial.println(F("This will be remove all records and cannot be undone"));

    delay(5000);                        // Give user enough time to cancel operation
    if (digitalRead(wipeB) == LOW) {    // If button still be pressed, wipe EEPROM
      Serial.println(F("Starting Wiping EEPROM"));
      for (int x = 0; x < EEPROM.length(); x = x + 1) {    //Loop end of EEPROM address
        if (EEPROM.read(x) == 0) {              //If EEPROM address 0
          // do nothing, already clear, go to the next address in order to save time and reduce writes to EEPROM
        }
        else {
          EEPROM.write(x, 0); 			// if not write 0 to clear, it takes 3.3mS
        }
      }
      Serial.println(F("EEPROM Successfully Wiped"));
    }
    else {
      Serial.println(F("Wiping Cancelled"));
    }
  }

  if (EEPROM.read(1) != 143) {
    Serial.println(F("No Master Card Defined"));
    Serial.println(F("Scan A Tag to Define as Master Card"));
    do {
      successRead = getID();            // sets successRead to 1 when we get read from reader otherwise 0
    }
    while (!successRead);    // Program will not go further while you not get a successful read

    for ( int j = 0; j < 4; j++ ) {
      EEPROM.write( 2 + j, readCard[j] );
    }
    EEPROM.write(1, 143);
    Serial.println(F("Master Card Defined"));
  }
  Serial.println(F("-------------------"));
  Serial.println(F("Master Card's UID"));
  for ( int i = 0; i < 4; i++ ) {          // Read Master Card's UID from EEPROM
    masterCard[i] = EEPROM.read(2 + i);    // Write it to masterCard
    Serial.print(masterCard[i], HEX);
  }
  Serial.println("");
  Serial.println(F("-------------------"));
  Serial.println(F("Everything Ready"));
  Serial.println(F("Waiting Tags to be scanned"));
}

void loop () {
  do {
    successRead = getID();
  }
  while (!successRead); 	//the program will not go further while you not get a successful read
  if (programMode) {
    if ( isMaster(readCard) ) { //If master card scanned again exit program mode
      Serial.println(F("Master Card Scanned"));
      Serial.println(F("Exiting Program Mode"));
      Serial.println(F("-----------------------------"));
      programMode = false;
      digitalWrite(redLed, LOW);      
      return;
    }
    else {
      if ( findID(readCard) ) { // If scanned card is known delete it
        Serial.println(F("I know this Tag, removing..."));
        deleteID(readCard);
        readConfirm();
        Serial.println("-----------------------------");
      }
      else {                    // If scanned card is not known add it
        Serial.println(F("I do not know this Tag, adding..."));
        writeID(readCard);
        readConfirm();
        Serial.println(F("-----------------------------"));
      }
    }
  }
  else {
    if ( isMaster(readCard) ) {  	// If scanned card's ID matches Master Card's ID enter program mode
      programMode = true;
      Serial.println(F("Hello Master - Entered Program Mode"));
      int count = EEPROM.read(0);
      Serial.print(F("I have "));
      Serial.print(count);
      Serial.print(F(" record(s) on EEPROM"));
      Serial.println("");
      Serial.println(F("Scan a Tag to ADD or REMOVE"));
      Serial.println(F("-----------------------------"));
      digitalWrite(redLed, HIGH);      
    }
    else {
      if ( findID(readCard) ) {	// If not, see if the card is in the EEPROM
        Serial.println(F("Welcome, you have access"));
        granted();
      }
      else {
        Serial.println(F("Good Bye, report this error to admin"));
        denied();
      }
    }
  }
}
