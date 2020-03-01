#define repeat_four(a) a;a;a;a;
#define repeat_six(a) a;a;a;a;a;a;
#define repeat_ten(a) a;a;a;a;a;a;a;a;a;a;
#define repeat_hundred(a) repeat_ten(repeat_ten(a))

#define gen_period(a, b) repeat_four(a) repeat_six(b)

void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  repeat_hundred(gen_period(PORTB = 0b1111111111, PORTB = 0))
}
