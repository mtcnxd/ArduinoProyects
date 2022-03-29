void sendGet(String val) {
  WiFiClient client;
  Serial.print("connecting ...");
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print("GET http://mototools.esy.es/webService/arduinoData.php?value=");
  client.println(val);
  client.println(" HTTP/1.1");
  client.println("Host: mototools.esy.es");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close");
  Serial.println("request sent: OK");
}
