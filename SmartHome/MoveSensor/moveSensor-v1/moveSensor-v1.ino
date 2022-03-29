static int movePin = 4;   // Digital In para el sensor de movimiento
static int lightPin = 5;  // Digital In para el sensor de luz
static int outputPin = 9; // Digital Output para el controlador de luz

void setup() {
  pinMode (movePin, INPUT);
  pinMode (lightPin, INPUT);
  pinMode (outputPin, OUTPUT);
}

void loop() {
  // Verificamos si la habitacion se encuentra oscura
  if (checkLight) {

    // Si hay movimiento y esta oscuro encendemos las luces del piso
    if (checkMove) {
      digitalWrite(outputPin, HIGH);
    } else {
      digitalWrite(outputPin, HIGH);
    }
  }
}

boolean checkLight() {
  bool light = digitalRead(lightPin);

  if (light) {
    return true;
  }
}

boolean checkMove() {
  bool movement = digitalRead(movePin);
  if (movement) {
    return true;
  }
}
