void setup() {
  // put your setup code here, to run once:
pinMode(3,OUTPUT);
}

void loop() {
  for(int i=0; i<266; i++){
    analogWrite(3,i);
    delay(1);
    }
  // put your main code here, to run repeatedly:
for(int k=255; k>0; k--){
    analogWrite(3,k);
    delay(1);
    }
}
