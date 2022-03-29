#include <SPI.h>
#include <SD.h>

File dataFile;
int contador = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Intentando escribir en la SD");
  pinMode(SS, OUTPUT);
  if (SD.begin(10)) {
    Serial.println("Memoria iniciada!");
  } else {
    Serial.println("Error de memoria!");
  }

  dataFile = SD.open("logFile.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println("Ocurrio algun error con el archivo");
    while (1);
  }
}

void loop() {
  if (contador <= 20) {
    String texto = "";
    
    int sensor = analogRead(A0);
    texto += contador;
    texto += "  ";
    texto += String(sensor);
    Serial.println(texto);    
    dataFile.println(texto);
    dataFile.flush();
  } else {
    Serial.println("Muestras exitosas");
    dataFile.close();
  }

  contador++;
  delay(500);
}
