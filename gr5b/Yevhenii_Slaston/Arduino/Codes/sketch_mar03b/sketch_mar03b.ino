double a;
byte a_old=0;
unsigned long micros_old=0;

void setup() {
  pinMode(A7, INPUT);
  Serial.begin(9600);

}

void loop() {
  a = analogRead(A7);
  a=map(a,0,1023,0,3);
  if(a==a_old){ }
  else{
  
 Serial.println(micros()-micros_old);
 micros_old=micros();
    
  }
  a_old=a;
 // delay(50);
}
