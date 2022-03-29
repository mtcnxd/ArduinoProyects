void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  randomSeed(micros());
}

void callback(char* topic, byte* payload, unsigned int length) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 00, "Temperature");

  String myString;
  for (int i = 0; i < length; i++) {
    Serial.print(payload[i]);
    myString += String((char)payload[i]);
  }
  display.drawString(0, 18, myString);
  display.display();
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection: ");
    Serial.println(mqttServer);

    if (client.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected to server");
      client.subscribe("mtcnxd/feeds/temperature");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
