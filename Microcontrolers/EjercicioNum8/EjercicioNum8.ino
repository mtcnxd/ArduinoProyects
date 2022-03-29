byte data[10] = {  
  B01111110,  B00001100,  B10110110,  B10011110,  B11001100, 
  B11011010,  B11111010,  B00001110,  B11111110,  B11001110
};
int Pines[7] = { 
  2,3,4,5,6,7,8 };
int array[4]={
  0,0,0,0};  
int Numero, Contador=0;

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
  if ( Serial.available() ){
    Numero = (Serial.read() - 48);
    array[3] = array[2];      
    array[2] = array[1];
    array[1] = array[0]; 
    array[0] = Numero;
    
    Serial.print("Numero aceptado: ");    
    Serial.print(array[Contador]);
    Serial.println(" ");    
  }
  for ( int i=3; i>=0; i-=1 ){
    DigitaNumero ( array[i],12-i );
    delay(5);
  }
}





