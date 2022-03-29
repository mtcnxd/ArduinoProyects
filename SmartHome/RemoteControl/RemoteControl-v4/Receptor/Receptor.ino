#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "Definitions.h"

RF24 radio(10, A0);

void setup(void) {
  Serial.begin(57600);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);
}

void loop(void)
{
  if ( radio.available() )
  {
    while (radio.available())
    {
      char data;
      radio.read(&data , sizeof(char));

      switch (data) {
        case '1':
          digitalWrite(outputPin, HIGH);
          delay(100);
          sendConfirm();

          break;
        case '2':
          digitalWrite(outputPin, LOW);
          break;
      }
    }
  }
}
