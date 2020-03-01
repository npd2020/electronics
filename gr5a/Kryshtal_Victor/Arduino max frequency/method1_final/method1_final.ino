#define repeat_ten(a) a;a;a;a;a;a;a;a;a;a;
#define repeat_hundred(a) repeat_ten(repeat_ten(a))

void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  repeat_hundred(PORTB = 0b1111111111; PORTB = 0)
}
