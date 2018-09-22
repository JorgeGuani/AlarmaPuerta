#define buzzer 6

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  alarma();
}

void alarma() {
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  delay(100);
}
