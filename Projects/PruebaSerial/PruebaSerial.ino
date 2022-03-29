int temp = 34;
int humidity = 50;
int ledPin = 13;
int contador = 0;
int retardo = 500;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.print(contador);
  Serial.print(",");
  contador ++;  
  Serial.print(contador);
  Serial.print(",");
  contador ++;  
  Serial.print(contador);
  Serial.print(",");  
  Serial.println();
  delay(retardo);

  if (Serial.available()) {
    char data = Serial.read();

    switch (data) {
      case ('A'):
        digitalWrite(ledPin, HIGH);
        retardo = 1000;
        break;

      case ('B'):
        digitalWrite(ledPin, LOW);
        retardo = 100;
        break;
    }
  }
}
