#define green 4 
#define red 5
boolean a=1;
long unsigned int t=0;
void setup() {
 // t=millis();
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);
}

void loop() {
  digitalWrite(green,a);
  digitalWrite(red,!a);
   
  if(millis()-t>1000){
    a=!a;
    t=millis();
  }
}
