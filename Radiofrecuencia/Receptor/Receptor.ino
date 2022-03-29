#include <VirtualWire.h>

int ledPin = 13;
int contador = 0;
const int buzzer = 2;
const int led = 3;
int rxPin = 6;
int setPoint = 36;

void setup() {
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_rx_pin(rxPin);
  vw_rx_start();
  pinMode (ledPin, OUTPUT);
  pinMode (led, OUTPUT);  
  Serial.begin(9600); 
  delay(500);  
}

void loop(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    for (int i = 0; i < buflen; i++) {
      
      int temp = buf[i];
      Serial.print ("Temperatura actual: ");
      Serial.println(temp);
      
      if (temp >= setPoint){
        alarma();
        digitalWrite(led, HIGH);
      } else {
        digitalWrite(led, LOW);        
      }
      
      if(contador == 1) {
        digitalWrite(ledPin, HIGH);
        contador = 0;
      } 
      else {
        digitalWrite(ledPin, LOW);
        contador = 1;
      }
    }
  }
  delay(300);
}


void alarma(){
  tone (buzzer, 100, 100);
  delay(100);
}
