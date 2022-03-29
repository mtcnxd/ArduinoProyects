#include <Servo.h> 
Servo myservo;
int Term, Giro;

void setup() {
    myservo.attach(9);
    Serial.begin(9600);
    myservo.write(0);
    delay(1000);
}

void loop() {
  Term = analogRead(A0);
  Term = (((5.0 * Term) * 100.0) / 1023.0);
  Serial.print(Term);
  Serial.println(" C");  
  Giro = map ( Term, 0,100,0,180 );
//  Serial.println(Giro);  
  myservo.write(Giro);
  delay(100);
}
