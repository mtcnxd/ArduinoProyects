#include <Wire.h>
#define SLAVE_ADDRESS 0x04
int option = 0;
int state = 0;

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {
  delay(100);
}

void receiveData(int byteCount){
  while(Wire.available()) {
    option = Wire.read();
    switch (option){
      case 1:
        digitalWrite(13, HIGH);
      break;
      case 2:
        digitalWrite(13, LOW);
      break;
      case 3:
        sendData();
      break;      
    }
  }
}

void sendData (){
  Wire.write(analogRead(A0));
}
