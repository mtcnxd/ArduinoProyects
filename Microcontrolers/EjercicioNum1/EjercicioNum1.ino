byte data[10] = {  
  B01111110,  B00001100,  B10110110,  B10011110,  B11001100, 
  B11011010,  B11111010,  B00001110,  B11111110,  B11001110
};
int Pines[7] = { 
  2,3,4,5,6,7,8 };

int dato[3] = {
  0,0,0};

int DigitaNumero (int Numero, int Posicion){
  int Contador = 1;  
  for (int i=9; i<=12; i++){
    if  (i == Posicion)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);    
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
  for ( int i=2; i<=12; i++ )
    pinMode(i, OUTPUT);
}

void loop() {
  for ( int i=0; i<=9999; i++ ){
    dato[0]=(i/1000)%10;
    DigitaNumero(dato[0], 9);
    delay(10);
    
    dato[1]=(i/100)%10;
    DigitaNumero(dato[1],10);    
    delay(10);    
    
    dato[2]=(i/10)%10;
    DigitaNumero(dato[2],11);    
    delay(10);    
    
    dato[3]=(i%10);
    DigitaNumero(dato[3],12);    
    delay(10);
  }  
}



