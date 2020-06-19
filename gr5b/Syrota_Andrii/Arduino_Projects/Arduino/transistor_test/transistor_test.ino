#define ON 2
#define OFF 4

void setup() {
pinMode(ON,OUTPUT);
pinMode(OFF,OUTPUT);
}

void loop() {
  digitalWrite(ON,HIGH);
  digitalWrite(OFF,LOW);
  delay(3000);
  digitalWrite(OFF,LOW);
  digitalWrite(ON,LOW);
  delay(3000);
  digitalWrite(OFF,HIGH);
  delay(3000);
}
