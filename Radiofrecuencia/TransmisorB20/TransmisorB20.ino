#include <VirtualWire.h>
#include <OneWire.h>

OneWire  ds(10);

char msg[1] = {'#'};

void setup(void) {
  Serial.begin(9600);

  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_tx_pin(4);
}

void loop(void) {
  Serial.print("Temp: ");
  Serial.println(temp());
  
  TransmitRF('5');
  
  delay(500);
}

void TransmitRF (char value) {
  msg = value;
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
}

float temp () {
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;

  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);

  delay(1000);

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);

  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } 
  else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;
    else if (cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  celsius = (float)raw / 16.0;
  return(celsius);
}
