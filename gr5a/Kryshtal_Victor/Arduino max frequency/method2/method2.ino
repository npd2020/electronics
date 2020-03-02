void setup() {
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);

  OCR1A = 0;
  TCCR1A = (1 << COM1A0);
  TCCR1B = (1 << WGM12) | (1 << CS10);

}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
}
