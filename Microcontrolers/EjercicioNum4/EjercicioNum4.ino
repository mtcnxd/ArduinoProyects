#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int valor;

byte Full[8] = {
  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,
};

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  valor = analogRead(A0);
  valor = map (valor, 0, 1023,0,16);

  lcd.createChar(1,Full);
  for (int i=0; i<=valor; i++){
    lcd.setCursor(i,1);
    lcd.write(1);
  }
  for (int i=16; i>=valor; i--){
    lcd.setCursor(i,0);
    lcd.write(1);
  }
  valor = analogRead (A0);
  valor = map (valor, 0,1023,0,255);
  analogWrite(10,valor-1);
  analogWrite(9,(255-valor));
  delay(200);
  lcd.clear();
}


