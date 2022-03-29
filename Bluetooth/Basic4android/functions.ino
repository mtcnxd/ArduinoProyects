void changeState (char valueRead) {
  switch (valueRead) {
    case 'A':
      digitalWrite(ledPin, HIGH);
      break;

    case 'B':
      digitalWrite(ledPin, LOW);
      break;
  }
}

void changeDimmer (int valueRead) {
  pwmValue = map(pwmValue, 0, 100, 0, 255);
  analogWrite(ledPwm, pwmValue);
}

