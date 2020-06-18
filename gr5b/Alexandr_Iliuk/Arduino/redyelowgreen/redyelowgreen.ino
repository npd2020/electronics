

void setup() {

  pinMode(4, OUTPUT);//red
  pinMode(6, OUTPUT);//yelow
  pinMode(8, OUTPUT);//green
}

void loop() {
  digitalWrite(4, HIGH);   // turn the red on
  delay(4000);                       // wait for a 4 second
  
  digitalWrite(6, HIGH);    // turn the yelow on
  delay(1000);                       // wait for a  second

  digitalWrite(4, LOW);// turn off red
  digitalWrite(6, LOW);// turn off yelow
  digitalWrite(8, HIGH);// turn on green
  delay(4000);

for (int i=0;i<3;i++){
  digitalWrite(8,LOW);
  delay(500);
  digitalWrite(8, HIGH);
  delay(500);
  }  //blink green

  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6,LOW);
}
