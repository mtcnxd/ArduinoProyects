void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  randomSeed(micros());

  Serial.print("WiFi connected. ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //String value = (String)(char)payload[0];
  //showMessage(value);  

  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
    showMessage("ENCENDIDO");  
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
    showMessage("APAGADO");
  }
}



void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection: ");
    Serial.println(mqttServer);

    if (client.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected to server");
      client.publish("mtcnxd/feeds/led", "Ready");
      client.subscribe("mtcnxd/feeds/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void showMessage(String msg) {
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}
