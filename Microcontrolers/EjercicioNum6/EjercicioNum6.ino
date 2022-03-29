byte data[10] = {  
  B01111110,  B00001100,  B10110110,  B10011110,  B11001100, 
  B11011010,  B11111010,  B00001110,  B11111110,  B11001110
};
int Pines[7] = { 
  2,3,4,5,6,7,8 };
int array[4]={
  0,0,0,0};  
int Valida, Contador=0, Muestra=0;

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
  if (Serial.available()){
    Valida = Serial.read();
    array[Contador] = Valida - 48;
    Contador++;

    if (Contador == 4){
      Serial.println("Mostrando estos datos: ");
      for ( int i=0; i<=3; i++ ){
        Serial.print(array[i]);
      }
      Contador = 0;

      for ( int j=0; j<=150; j++ ){
        for ( int i=0; i<=3; i++ ){
          DigitaNumero ( array[i],i+9 );
          delay(5);
        }
      }
      digitalWrite(12,LOW);
      Serial.println("\n\rIntroduce otros datos");      
    }
  }
}





