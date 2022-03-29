void sendConfirmStart () {
  radio.openWritingPipe(pipe);
  radio.write( "S" , 1 );
}

void sendConfirmOn () {
  radio.stopListening();
  radio.openWritingPipe(pipe);
  radio.write( "1" , 1 );
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void sendConfirmOff () {
  radio.stopListening();
  radio.openWritingPipe(pipe);
  radio.write( "2" , 1 );
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void setOutput(int _dataRead) {
  switch ( _dataRead ) {
    case 1 :
      if (bitRead(PORTD, 4)) {
        digitalWrite(outputPin, LOW);
        digitalWrite(pilotPin, HIGH);
        sendConfirmOff();
      } else {
        digitalWrite(outputPin, HIGH);
        digitalWrite(pilotPin, LOW);
        sendConfirmOn();
      }
      break;
  }
}
