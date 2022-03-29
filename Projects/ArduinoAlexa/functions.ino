void firstLightChanged(uint8_t brightness) {
  Serial.print("Device 1 changed to ");

  if (brightness) {
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else  {
    Serial.println("OFF");
  }
}


void secondLightChanged(uint8_t brightness) {
  //do what you need to do here
}


void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi() {
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
