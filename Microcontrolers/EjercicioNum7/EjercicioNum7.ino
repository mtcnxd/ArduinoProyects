byte data[10] = {  
  B01111110,  B00001100,  B10110110,  B10011110,  B11001100, 
  B11011010,  B11111010,  B00001110,  B11111110,  B11001110
};
int Pines[7] = { 
  2,3,4,5,6,7,8 };
int Pot1,Pot2, Digito; 

int DigitaNumero (int Numero, int Posicion){
  int Contador = 1;  
  for (int i=9; i<=12; i++){
    if  (i == Posicion){
      digitalWrite(i,HIGH);
    } 
    else {
      digitalWrite(i,LOW);    
    }
  }  
  for( byte i=Numero; i<=Numero; i++) {
    for ( byte j=0; j<=7; j++) {
      digitalWrite( Contador, bitRead(data[i], j));
      Contador++ ;      
    }
    Contador = 1;
    break;      
  }
}

void setup() {
  for ( int i=2; i<=12; i++ ){
    pinMode( i, OUTPUT );
  }
  Serial.begin( 9600 );
}

void loop() {
  Pot1 = map (analogRead(A0),0,1023,0,99);
  Digito = Pot1/10;
  DigitaNumero ( Digito,9 );
  delay(5);  
  Digito = Pot1%10;
  DigitaNumero ( Digito,10 );
  delay(5); 
  
  Pot2 = map (analogRead(A1),0,1023,0,99);
  Digito = Pot2/10;
  DigitaNumero ( Digito,11 );
  delay(5);  
  Digito = Pot2%10;
  DigitaNumero ( Digito,12 );
  delay(5);    
}
