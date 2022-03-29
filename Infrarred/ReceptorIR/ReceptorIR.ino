#include <WProgram.h>
#include <NECIRrcv.h>
#define IRPIN 8

NECIRrcv ir(IRPIN);

int LED = 10; 
int VENTILADOR = 11;

int counter1 = 0;
int counter2 = 0;

void setup() {
  Serial.begin(9600);
  ir.begin();
  pinMode(LED,OUTPUT);
  pinMode(VENTILADOR, OUTPUT);
}

void loop() {
  String ircode; 

  while (ir.available()) {
    ircode = ir.read(); 

    Serial.println(ircode);

    if (ircode == "1711591394") {
      delay (50);
      if (counter1 == 0){
        digitalWrite(LED, HIGH);
        counter1 = 1 ;
      } 
      else {
        digitalWrite(LED, LOW);
        counter1 = 0 ;
      }
    } 
    else if (ircode == "16670877") {
      delay (50);
      if (counter2 == 0){
        digitalWrite(VENTILADOR, HIGH);
        counter2 = 1 ;
      } 
      else {
        digitalWrite(VENTILADOR, LOW);
        counter2 = 0 ;
      }   
    } 
  }
}

