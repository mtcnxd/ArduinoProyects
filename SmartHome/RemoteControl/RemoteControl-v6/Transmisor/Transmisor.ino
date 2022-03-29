#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "Definitions.h"

RF24 radio(10, A0);

char data;

void setup(void)
{
  Serial.begin(57600);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop(void)
{
  if ( Serial.available() || radio.available() )
  {
    radio.read( &data, sizeof(data) );
    Serial.println(data);

    char letra = Serial.read();
    sendData(letra);
  }

  delay(100);
}
