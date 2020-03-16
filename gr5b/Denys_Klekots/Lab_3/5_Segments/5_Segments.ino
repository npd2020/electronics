void setup() {

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

int i=0;

void loop() {

  if(i==5){
    i=0;

    for(int j=0;j<5;j++)
      digitalWrite(9+i,LOW);
    
  }

  digitalWrite(9+i,HIGH);

  i++;

}
