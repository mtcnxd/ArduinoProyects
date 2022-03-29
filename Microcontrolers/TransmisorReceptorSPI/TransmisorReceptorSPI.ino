int Cs=10, Data=11, Clock=12;
int CsR=7, DataR=8, ClockR=9;
int contador = 1;
int ByteSend = 0;
int ByteSave = 0;
int Valida = 0;
int statusClk = 0;
int var = 0;
int i = 0, ToDo = 0;
int data_received[8];
int Info[8] = {
  0,0,0,0,0,0,0,0};

void recibir(){
  if (digitalRead(CsR) == LOW) {
    while (digitalRead(ClockR) == HIGH) {
      if (i<8){    
        data_received[i]= digitalRead(DataR);
        i++; 
        delay(200);
      }
    } 
    if (i==8){
      i=0;
      Serial.print("Datos recibidos: ");
      Serial.println(" "); 
      for (i=0;i<8;i++){
        Serial.print(data_received[i]);
      }
      Serial.println(" ");
      var= (data_received[7]*1) + (data_received[6]*2) + (data_received[5]*4) + (data_received[4]*8) + (data_received[3]*16) + (data_received[2]*32) + (data_received[1]*64) + (data_received[0]*128);
      Serial.print("valor decimal: ");
      Serial.print(var); 
      Serial.println(" ");    
    }
  }
  else {
    i=0;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(Cs, OUTPUT);
  pinMode(Data, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(CsR, INPUT);
  pinMode(DataR, INPUT);
  pinMode(ClockR, INPUT);  
  digitalWrite(Clock, HIGH);  
}

void loop() {
  if (Serial.available()){
    Valida = Serial.read();
    Info[ByteSave] = Valida - 48;
    ByteSave++;
    if (ByteSave == 8){
      for ( int i=0; i<=7; i++ ){
        Serial.print(Info[i]);
      }
      Serial.println(" Datos a enviar");
      delay(200);
    }
  }

  if (Valida == 46){
    digitalWrite(Cs,LOW);
    delay(50);
    digitalWrite(Clock, LOW);
    for (int i=1; i<=16; i++) {
      if (statusClk == 0){
        if (Info[ByteSend] == 1){
          digitalWrite( Data,HIGH );
        } 
        else {
          digitalWrite(Data,LOW);        
        }
        Serial.print( Info[ByteSend] );
        delay(100);
        digitalWrite(Clock, HIGH);
        statusClk = 1;
        ByteSend++;        
      } 
      else {   
        delay(100);
        digitalWrite( Clock,LOW );
        statusClk = 0;         
      }
    }
    Serial.println(" Completado!");
    ByteSend = 0;
    ByteSave = 0;
    Valida = 0;
  } 
  else {
    digitalWrite(Cs,HIGH); 
    delay(25);   
    digitalWrite(Data, LOW);
    recibir();
  }  

}



