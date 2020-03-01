void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  PORTB = 0b11111111;
  PORTB = 0;
}
