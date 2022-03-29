#include <idDHT11.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int idDHT11pin = 2;
int idDHT11intNumber = 0;
int option = 0, mensaje = 0;
RTC_DS1307 rtc;

void dht11_wrapper();
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void setup() {
  Wire.begin();  
  lcd.begin(16, 2);  
  rtc.begin();
  //rtc.adjust(DateTime(__DATE__,__TIME__));
  Serial.begin(9600);
}
void dht11_wrapper() {
  DHT11.isrCallback();
}
void loop() {
  DHT11.acquire();
  DateTime now = rtc.now();  

  while (DHT11.acquiring());

  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Temp");
  lcd.setCursor(5, 0);
  lcd.print(DHT11.getCelsius(), 0);  
  Serial.print("Temp:");
  Serial.println(DHT11.getCelsius(), 0);    
  lcd.setCursor(8, 0);
  lcd.print("Hum");  
  lcd.setCursor(12,0);
  lcd.print(DHT11.getHumidity(), 0);
  lcd.setCursor(14,0);  
  lcd.print("%");

  if (analogRead(A0) >= 630 && analogRead(A0) <= 650) {
    lcd.clear();
    if (mensaje == 0) {
      mensaje = 1;
    } 
    else {
      mensaje = 0;
    }
  } 
  else if ( analogRead(A0) >= 245 && analogRead(A0) <= 365 ){
    if (option == 0) {
      option = 1;
    } 
    else {
      option = 0;
    }
  } 

  if ( option == 0 ) {
    lcd.setCursor(0,1); 
    lcd.print("Time");
    lcd.setCursor(5,1);   
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    lcd.print(now.second(), DEC);  
  } 
  else {
    lcd.setCursor(0,1); 
    lcd.print("Date");
    lcd.setCursor(5,1);   
    lcd.print(now.day(), DEC);
    lcd.print("/");
    lcd.print(now.month(), DEC);
    lcd.print("/");
    lcd.print(now.year(), DEC);
  }

  if (mensaje == 1) {
    lcd.clear();
    lcd.setCursor(0,0);     
    lcd.print("TE AMO CINDY");
  }
  
  if (now.minute() == 0) {
    alarma();
  }
  delay(500);  
}


void alarma(){
  tone(3, 50, 20);
}
