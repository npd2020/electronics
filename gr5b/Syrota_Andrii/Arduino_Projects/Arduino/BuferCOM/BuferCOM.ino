int val = 0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
    Serial.print("I received: ");
    Serial.println(val);
    delay(250);
  }
}
