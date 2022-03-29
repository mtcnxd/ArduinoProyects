void checkOn() {
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(defrostPin, OUTPUT);

  digitalWrite(ledPin, HIGH);
  digitalWrite(motorPin, HIGH);
  digitalWrite(defrostPin, HIGH);
  setupWiFi();
  for (int i = 0; i <= 10; i++) {
    Serial.print(".");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  //eraseEeproom();
  Serial.println();
  Serial.println("Check On: OK");
  digitalWrite(ledPin, HIGH);
}

void eraseEeproom() {
  for (int i = 0; i <= 255; i++) {
    EEPROM.write(i, 0);
    delay(10);
  }
  Serial.println("Erase MEM: OK");
}

void setupWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  randomSeed(micros());
  Serial.println();
  Serial.print("WiFi connected. ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void showInfoSerial() {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" CoolingMode: ");
  Serial.print(coolingMode);
  Serial.print(" Running: ");
  Serial.print(runningTimer);
  Serial.print(" Waiting: ");
  Serial.println(waitingTimer);
}

void waitForRun() {
  //unsigned long current = millis();

  //###### Si el tiempo transcurrido es mayor a 60 segundos #####//
  if (currentMillis - previous >= interval) {
    previous = currentMillis;
    snprintf (mins, 10, "%ld", runningTimer);
    client.publish("mtcnxd/feeds/time", mins);

    // Esperamos que sleepTimer llegue a 40 mins
    if (waitingTimer >= sleepTimer) {
      coolingMode = true;
      waitingTimer = 0;
    } else {
      if (waitingTimer <= 9) {
        defrost();
      } else {
      }
      coolingMode = false;
      runningTimer = 0;
      waitingTimer++;
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
    ecoModeWriteState(0);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
    ecoModeWriteState(1);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
      client.subscribe("mtcnxd/feeds/eco");
      client.subscribe("mtcnxd/feeds/configure");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void cooling() {
  Serial.println("Status: COOLING");
  digitalWrite(motorPin, LOW);
  client.publish("mtcnxd/feeds/status", "COOLING");
}

void waiting() {
  Serial.println("Status: WAITING");
  digitalWrite(motorPin, HIGH);
  digitalWrite(defrostPin, HIGH);
  client.publish("mtcnxd/feeds/status", "WAITING");
}

void defrost() {
  Serial.println("Status: DEFROST");
  digitalWrite(defrostPin, LOW);
  client.publish("mtcnxd/feeds/status", "DEFROST");
}

void ecoModeWriteState(int state) {
  EEPROM.write(0, state);
}

int ecoModeReadState() {
  return  EEPROM.read(0);
}

int configureTemp(int value) {
  EEPROM.write(1, value);
}
