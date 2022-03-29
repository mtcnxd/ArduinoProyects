void sendData (char data) {
  radio.stopListening();
  radio.openWritingPipe(pipe);

  switch (data) {
    case '1':
      radio.write( "1" , 1 );
      break;
  }

  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
