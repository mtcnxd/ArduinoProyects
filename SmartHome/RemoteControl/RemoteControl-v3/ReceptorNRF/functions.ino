void setOutput(int _dataRead) {
  switch ( _dataRead ) {
    case 1 :
      if (bitRead(PORTD, 4)) {
        digitalWrite(outputPin, LOW);
        digitalWrite(pilotPin, HIGH);
      } else {
        digitalWrite(outputPin, HIGH);
        digitalWrite(pilotPin, LOW);
      }
      break;
  }
}

void configureRF() {
  Mirf.csnPin = A0;
  Mirf.cePin = 10;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"TX_01");
  Mirf.payload = 1;
  Mirf.config();
}

void sendUnicId(){

}
