void setup() {
  pinMode(A7, INPUT);
  Serial.begin(9600);

}

void loop() {
  double a = analogRead(A7);
  Serial.println(a);
  delay(50);

}
