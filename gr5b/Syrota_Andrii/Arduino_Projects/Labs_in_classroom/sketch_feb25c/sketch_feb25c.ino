void setup() {
  ADCSRA = 0b11100010;
  ADMUX = 0b11100100;
pinMode(9,OUTPUT);
}

void loop() {
  analogWrite(9,200);
 // delay(100);
 // analogWrite(9,100);
  //delay(100);
 // analogWrite(9,50);
}
