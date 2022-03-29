#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "Definitions.h"

RF24 radio(10, A0);

void setup(void) {
  Serial.begin(57600);

  radio.begin();

  pinMode(outputPin, OUTPUT);
  delay(500);
  digitalWrite(outputPin, HIGH);

  sendConfirmStart();

  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop(void)
{
  byte data;

  if (digitalRead(switchRightPin) == HIGH) {
    if (digitalRead(switchLeftPin) == LOW) {
      if (canChange) {
        canChange = false;
        setOutput(toggle);
      }
    }
  } else if (digitalRead(switchRightPin) == LOW) {
    if (digitalRead(switchLeftPin) == HIGH) {
      if (!canChange) {
        canChange = true;
        setOutput(toggle);
      }
    }
  }


  if ( radio.available() )
  {
    while (radio.available())
    {
      char data;
      radio.read(&data , sizeof(char));

      switch (data) {
        case '1':
          setOutput(toggle);
          delay(100);
          sendConfirmOn();
          break;
      }
    }
  }
}
