#include <idDHT11.h>
#include <VirtualWire.h>

const int ledPin = 13;
const int ledAlarm = 3;
const int mtrPin = 12;
int SensorValue = 0;
int setPoint = 36;
char msg[1] = {
  '#'};


void dht11_wrapper();
idDHT11 DHT11(2,0,dht11_wrapper);

void setup() {
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_tx_pin(4);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(mtrPin, OUTPUT);
  pinMode(ledAlarm, OUTPUT);  
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);  
  delay(1000);  
}

void dht11_wrapper() {
  DHT11.isrCallback();
}

void loop() {
  DHT11.acquireAndWait();
  SensorValue = DHT11.getCelsius();
  
  if (SensorValue >= setPoint){
    digitalWrite(mtrPin, HIGH);
    digitalWrite(ledAlarm, HIGH);    
  } else {
    digitalWrite(mtrPin, LOW);    
    digitalWrite(ledAlarm, LOW);     
  }
  
  TransmitRF(SensorValue);  
  Serial.print("Temperatura: ");
  Serial.println(SensorValue);
  
// SensorValue = DHT11.getHumidity();
// TransmitRF(SensorValue);  
// Serial.print("  Humi: ");  
// Serial.println(SensorValue);  
//  delay(1000);
}

void TransmitRF (int value) {
  msg[0] = value;  
  digitalWrite(ledPin, HIGH);
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx();
  delay(100);
  digitalWrite(ledPin, LOW);  
  delay(100);  
}
