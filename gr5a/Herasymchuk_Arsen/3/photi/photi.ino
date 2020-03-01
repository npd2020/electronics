int a = A0;    // select the input pin for the potentiometer
int b=0;
void setup() {
  Serial.begin(9600);
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (10, OUTPUT);
}

void loop() {
  b=analogRead(a);
  for(int i=0;i<5; i++){
    digitalWrite(2+2*i, LOW);

  }
  Serial.println(b);  
  if ((b<=450)&&(b>380)){
    digitalWrite(2, HIGH);
    for(int i=1; i<5; i++){
    digitalWrite(2+2*i, LOW);
  }
  }
  if ((b<=380)&&(b>280)){
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    for(int i=2; i<5; i++){
    digitalWrite(2+2*i, LOW);
  }
  }
  if ((b<=280)&&(b>180)){
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
    
    for(int i=3; i<5; i++){
    digitalWrite(2+2*i, LOW);
  }
  }
  if ((b<=180)&&(b>80)){
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    for(int i=4; i<5; i++){
    digitalWrite(2+2*i, LOW);
  }
  }
  if ((b<=80)&&(b>30)){
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
  }    
  }
