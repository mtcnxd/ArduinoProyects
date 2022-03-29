#include <ESP8266WiFi.h>

const char* ssid      = "Backup_CSL";
const char* password  = "100%backup";
const char* host  = "mototools.esy.es";
const int httpsPort   = 80;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  String nombre = "Marcos";
  sendGetData(nombre);
  delay(10 * 60);
}


void sendGetData(String val) {
  WiFiClient client;
  Serial.print("connecting ...");
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print("GET http://mototools.esy.es/webService/arduinoData.php?texto=");
  client.println(val);
  client.println(" HTTP/1.1");
  client.println("Host: mototools.esy.es");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close");
  Serial.println("request sent: OK");
}
