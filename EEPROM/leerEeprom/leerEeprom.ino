#include <EEPROM.h>

int addr = 0;
int leer = 1;
int valor = 0;
float voltaje = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (leer == 1) {
    valor = EEPROM.read(0);
    voltaje = valor * (5.0/255.0);
    Serial.print("Voltaje: ");
    Serial.println(voltaje, DEC);
    
    Serial.print("Horas: ");
    Serial.println(EEPROM.read(1));
    
    Serial.print("Minutos: ");
    Serial.println(EEPROM.read(2));

    Serial.print("Segundos: ");
    Serial.println(EEPROM.read(3));    
  }
  leer = 0;
}


