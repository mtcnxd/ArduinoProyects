#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <TimerOne.h>
#include "definitions.h"

void setup() {
  Serial.begin(9600);  

  pinMode(AC_pin, OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(ledIndicator,OUTPUT);  

  attachInterrupt(1, zero_cross_detect, FALLING);
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(dim_check, freqStep);

  Mirf.spi=&MirfHardwareSpi;
  Mirf.init();  
  Mirf.setRADDR((byte *)"TX_01");
  Mirf.payload = 1; 
  Mirf.config();

  SPI.setClockDivider(SPI_CLOCK_DIV128);
}

void loop() {
  if (Serial.available()){
    char value = Serial.read();
    changeSpeed(value);
  }
  
  int value = RFdata();

  if (value){
    Serial.println(value);
    if(value == 255){
      digitalWrite(ledIndicator, HIGH);
    }else {
      digitalWrite(ledIndicator, LOW);
    }
  }
  delay(50);
}


