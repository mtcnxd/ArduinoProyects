void enviarDatos(int value) {
  loxone.beginPacket(host, port);
  loxone.print(value);
  loxone.endPacket();  
}
