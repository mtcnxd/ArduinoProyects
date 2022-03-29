#include <LCD5110_Graph.h>

LCD5110 myGLCD(8, 9, 10, 11, 12);

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t happy[];
extern uint8_t termometer[];
extern uint8_t doggi[];
extern uint8_t healt[];
extern uint8_t inicio[];
extern uint8_t bateria[];
extern uint8_t correo[];

const int pinBacklight = 6;
int intensidad = 255;

void setup() {
  for (int i = 0; i <= intensidad; i++) {
    analogWrite(pinBacklight, i);
    delay(2);
  }
  analogWrite(pinBacklight, intensidad);

  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("Battery: 50%", 0, 0);
  myGLCD.drawBitmap(76, 0, bateria, 8, 8);
  myGLCD.drawBitmap(35, 15, correo, 11, 8);  
  myGLCD.print("(1)New Mail", CENTER, 30);
  myGLCD.update();
  delay(2000);
  delay(2000);
}

void loop() {
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, happy, 8, 8);
  myGLCD.print("Happy", 10, 1);

  myGLCD.drawBitmap(0, 10, termometer, 8, 8);
  myGLCD.print("Temp", 10, 10);

  myGLCD.drawBitmap(0, 20, doggi, 8, 8);
  myGLCD.print("Doggi", 10, 20);

  myGLCD.drawBitmap(0, 30, healt, 8, 8);
  myGLCD.print("Healt", 10, 30);

  myGLCD.drawBitmap(0, 40, inicio, 8, 8);
  myGLCD.print("Home", 10, 40);

  myGLCD.update();
  delay(1000);
}
