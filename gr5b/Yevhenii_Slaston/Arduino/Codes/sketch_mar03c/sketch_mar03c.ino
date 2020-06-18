double a;
int i=0;
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
   if(a != a_old &&i){
   a_old=a;
  i=0;
  }
  if(i==0&&a==a_old)
   
    micros_old-=micros();
     i=1;
     a=a_old;
  
  Serial.println(micros_old);
  

 // delay(50);
}
