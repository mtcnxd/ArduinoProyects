int sensorPin = 3;
int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  boolean sensorTrue = digitalRead(sensorPin);
  
  if (sensorTrue) {
    Serial.println("Sensor OK");
    digitalWrite(ledPin, sensorTrue);
  } else {
    Serial.println("Sensor ERROR");
    digitalWrite(ledPin, sensorTrue);    
  }

  delay(100);
}
