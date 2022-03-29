int getID() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
//  Serial.println(F("Scanned PICC's UID:"));
  for (int i = 0; i < 4; i++) {
    readCard[i] = mfrc522.uid.uidByte[i];
//    Serial.print(readCard[i], HEX);
  }
//  Serial.println("");
  mfrc522.PICC_HaltA();
  return true;
}

void granted () {
  digitalWrite(redLed, HIGH);
  digitalWrite(relay, HIGH);
  delay(2000);
  digitalWrite(relay, LOW);
  digitalWrite(redLed, LOW);
  delay(1000);
}

void denied() {
  digitalWrite(redLed, HIGH);
  delay(100);
  digitalWrite(redLed, LOW);
  delay(100);
  digitalWrite(redLed, HIGH);
  delay(100);
  digitalWrite(redLed, LOW);
  delay(500);
}

void readID( int number ) {
  int start = (number * 4 ) + 2;
  for ( int i = 0; i < 4; i++ ) {
    storedCard[i] = EEPROM.read(start + i);
  }
}

void writeID( byte a[] ) {
  if ( !findID( a ) ) {
    int num = EEPROM.read(0);
    int start = ( num * 4 ) + 6;
    num++;
    EEPROM.write( 0, num );
    for ( int j = 0; j < 4; j++ ) {
      EEPROM.write( start + j, a[j] );
    }
//    Serial.println(F("Succesfully added ID record to EEPROM"));
  }
  else {
//    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));
  }
}

void deleteID( byte a[] ) {
  if ( !findID( a ) ) {
//    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));
  }
  else {
    int num = EEPROM.read(0);
    int slot;
    int start;
    int looping;
    int j;
    int count = EEPROM.read(0);
    slot = findIDSLOT( a );
    start = (slot * 4) + 2;
    looping = ((num - slot) * 4);
    num--;
    EEPROM.write( 0, num );
    for ( j = 0; j < looping; j++ ) {
      EEPROM.write( start + j, EEPROM.read(start + 4 + j));
    }
    for ( int k = 0; k < 4; k++ ) {
      EEPROM.write( start + j + k, 0);
    }
    Serial.println(F("Succesfully removed ID record from EEPROM"));
  }
}

boolean checkTwo ( byte a[], byte b[] ) {
  if ( a[0] != NULL )
    match = true;
  for ( int k = 0; k < 4; k++ ) {
    if ( a[k] != b[k] )
      match = false;
  }
  if ( match ) {
    return true;
  }
  else  {
    return false;
  }
}

int findIDSLOT( byte find[] ) {
  int count = EEPROM.read(0);
  for ( int i = 1; i <= count; i++ ) { 		// Loop once for each EEPROM entry
    readID(i); 								// Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( find, storedCard ) ) { 	// Check to see if the storedCard read from EEPROM
      // is the same as the find[] ID card passed
      return i; 				// The slot number of the card
      break; 					// Stop looking we found it
    }
  }
}

boolean findID( byte find[] ) {
  int count = EEPROM.read(0);
  for ( int i = 1; i <= count; i++ ) {
    readID(i);
    if ( checkTwo( find, storedCard ) ) {
      return true;
      break;
    }
    else {
    }
  }
  return false;
}

boolean isMaster( byte test[] ) {
  if ( checkTwo( test, masterCard ) )
    return true;
  else
    return false;
}

void readConfirm() {
  digitalWrite(redLed, LOW);
  delay(200);
  digitalWrite(redLed, HIGH);
}
