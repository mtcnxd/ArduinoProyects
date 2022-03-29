void showLoader(String texto, int x, int y, int wait) {
  for (int i = 0; i < 128; i++) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(texto);

    display.drawRect(x, y, 128, 3, WHITE);
    display.fillRect(x, y, i, 3, WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(x + 55, y + 6);
    display.println(map(i, 0, 128, 0, 100));
    display.setCursor(x + 67, y + 6);
    display.println("%");
    display.display();
    delay(wait);
  }
}

void showChar(String c, int x, int y) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(c);
  display.display();
}

int getTemp() {
  DHT11.acquire();
  while (DHT11.acquiring());
  return DHT11.getCelsius();
}

int getHumi() {
  DHT11.acquire();
  while (DHT11.acquiring());
  return DHT11.getHumidity();
}
