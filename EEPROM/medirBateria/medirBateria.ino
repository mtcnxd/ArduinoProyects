#include <EEPROM.h>

float volts = 0;
int segundos = 0;
int minutos = 0;
int horas = 0;
int address = 0;

int currentMillis = 0;
int antesMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  currentMillis = millis();

  if (currentMillis - antesMillis >= 1000) {
    antesMillis = currentMillis; 

    int valor = analogRead(A0);
    valor = map (valor, 0, 1023, 0, 255);

    if (valor >= 35){
      EEPROM.write(address, valor);  // Guardo el valor del ADC
      EEPROM.write(address + 1, horas);   
      EEPROM.write(address + 2, minutos);
      EEPROM.write(address + 3, segundos);       
      digitalWrite(13, HIGH);
      delay(50);      
      digitalWrite(13, LOW);
      Serial.println(segundos);
    } 
    else {
      digitalWrite(13, HIGH);
    }

    if (minutos >= 60) {
      horas++;
      minutos = 0;
      segundos = 0;
    }
    if (segundos >= 60) {
      minutos++;
      segundos = 0;
    } 
    else {
      segundos++;   
    }
  }
} 


