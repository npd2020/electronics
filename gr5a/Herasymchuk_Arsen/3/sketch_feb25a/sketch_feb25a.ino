void setup() {
  Serial.begin(9600);
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (10, OUTPUT);
}

void loop() {
  for(int i=0;i<5; i++){
    digitalWrite(2+2*i, LOW);

}
  for(int i=0; i<5; i++){
    digitalWrite(2+2*i, HIGH);
    delay (100);
  }
  for(int i=0; i<5; i++){
    digitalWrite(10-2*i, LOW);
    delay (100);
  }
    
    
    
  }
