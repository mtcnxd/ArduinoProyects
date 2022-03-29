void sendData (char data) {
  radio.stopListening();
  radio.openWritingPipe(pipe);

  switch (data) {
    case '1':
      radio.write( "1" , 1 );
      Serial.println("Encendido");
      break;
    case '2':
      radio.write( "2" , 1 );
      Serial.println("Apagado");
      break;
  }

  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
