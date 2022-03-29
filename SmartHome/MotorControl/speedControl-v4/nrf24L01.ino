byte RFdata(){
  byte data;
  
  if( Mirf.dataReady() ) {
    Mirf.getData(&data);
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);    
  }
  return data;      
}
