int getID() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
  for (int i = 0; i < 4; i++) {
    readCard[i] = mfrc522.uid.uidByte[i];
  }
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
  }
  else {
  }
}

void deleteID( byte a[] ) {
  if ( !findID( a ) ) {
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
  for ( int i = 1; i <= count; i++ ) {
    readID(i);
    if ( checkTwo( find, storedCard ) ) {
      return i;
      break;
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
