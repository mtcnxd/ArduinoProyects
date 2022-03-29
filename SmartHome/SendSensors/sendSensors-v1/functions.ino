void sendServer(String sens, int val) {
  WiFiClient client;
  Serial.println("Sending data ...");
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print("GET http://mototools.esy.es/webService/saveDataArduino.php?sensor=");
  client.print(sens);
  client.print("&value=");
  client.println(val);
  client.println(" HTTP/1.1");
  client.println("Host: mototools.esy.es");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close");
  //Serial.println("request sent: OK");
}

void getServer() {
  //Serial.print("connecting to ");
  //Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    //Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n\r\n");
  delay(500); // wait for server to respond
  String section = "header";

  while (client.available()) {
    String line = client.readStringUntil('\r');
    //Serial.print(line);    // we’ll parse the HTML body here

    if (section == "header") { // headers..
      //Serial.print(".");
      if (line == "\n") { // skips the empty space at the beginning
        section = "json";
      }
    }
    else if (section == "json") { // print the good stuff
      section = "ignore";
      String result = line.substring(1);      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);

      if (!json_parsed.success()) {
        Serial.println("parseObject() failed");
        return;
      }

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed[jsonObj], "true") == 0) {
        digitalWrite(outputPin, HIGH);
        //Serial.println("TRUE");
      } else {
        digitalWrite(outputPin, LOW);
        //Serial.println("FALSE");
      }
    }
  }
}
