#include <Arduino.h>

const char* ssid = "HOFFEN_IoT";
const char* password = "H0ffen.147";

String url = "https://api.bitso.com/v3/ticker/?book=";
String coin[] = {"bch_mxn", "bat_mxn", "ltc_mxn"};

int timeUpdate = 5000;
