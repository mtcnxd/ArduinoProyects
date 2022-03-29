/*
  Cambio de configuracion del modulo bluetooth mediante comandos AT
  para ello el modulo no debe estar vinculado con ningun dispositivo
  bluetooth, en mi caso el led debe estar en modo intermitente, si esta
  vinculado aparece encendido de forma permanente
*/

int state = false;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  digitalWrite(13, LOW);
}

void loop() {
  if (state == false) {
    changeName();
    state = true;
    
  } else {
    correcto();
  }
}

void changeName() {
  digitalWrite(13, HIGH);
  /*
    Tiempo de espera de 15 segundos (prudencial, se puede cambiar, depende de lo que tardes
    en volver a conectarlos) para reconectar cables RX y TX del modulo bluetooth
    a la placa Arduino ya que para programar esta deben estar desconectados
  */
  delay(15000);
  //Indicacion de tiempo de espera finalizado
  digitalWrite(13, LOW);
  //Iniciamos comunicacion con modulo bluetooth mediante comandos AT
  Serial.print("AT");
  //Espera de 1 segundo según datasheet entre envio de comandos AT
  delay(1000);
  //Cambio de nombre donde se envia AT+NAME y seguido el nombre que deseemos
  Serial.print("AT+NAMELedStrip");
  //Espera de 1 segundo según datasheet entre envio de comandos AT
  delay(1000);
  /*
    Cambio de la velocidad del modulo en baudios
    Se envia AT+BAUD y seguido el numero correspondiente:

    1 --> 1200 baudios
    2 --> 2400 baudios
    3 --> 4800 baudios
    4 --> 9600 baudios (por defecto)
    5 --> 19200 baudios
    6 --> 38400 baudios
    7 --> 57600 baudios
    8 --> 115200 baudios
  */

  Serial.print("AT+BAUD4");
  //Espera de 1 segundo según datasheet entre envio de comandos AT
  delay(1000);
  //Configuracion Password, se envia AT+PIN y seguido password que queremos
  Serial.print("AT+PIN1234");
  //Espera de 1 segundo según datasheet entre envio de comandos AT
  delay(1000);

  Serial.print("OK Cambios Realizados correctamente");
  digitalWrite(13, HIGH);
}

void correcto() {
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);
  delay(300);
}
