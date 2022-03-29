byte data[10] = {  
  B01111110,  B00001100,  B10110110,  B10011110,  B11001100, 
  B11011010,  B11111010,  B00001110,  B11111110,  B11001110
};
int Pines[7] = { 
  2,3,4,5,6,7,8 };

int Contador1, Contador2, Valor;

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

int remote(){
  int value = 0;  
  int time = pulseIn(12,LOW);  
  if(time>2000){  
    for(int counter1=0;counter1<12;counter1++){  
      if(pulseIn(12,LOW)>1000){  
        value = value + (1<< counter1);
      }  
    }  
  }  
  return value;  
}

void setup() {
  for ( int i=2; i<=12; i++ )
    pinMode(i, OUTPUT);

  Serial.begin(9600);

  pinMode(12,INPUT);
  pinMode(13,INPUT);  
}

void loop() {
  Valor = Serial.read();
  if (Valor == 1){
    Contador1 += 1;
  }

  if (Valor == 2){
    Contador2 += 1;
  }

  int remote_val = remote();  
  if(remote_val>100){
    Serial.println(remote_val);    
    delay(5);
  } 
  DigitaNumero(Contador1, 10);
  delay(50);
  DigitaNumero(Contador2, 11); 
}

