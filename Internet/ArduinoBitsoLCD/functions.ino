void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Conecting ...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);    
  }

  //lcd.backlight();  
  randomSeed(micros());

  Serial.print("WiFi connected. ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
}
