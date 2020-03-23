void setup() {
  
  pinMode (10,OUTPUT);
  pinMode (11,OUTPUT);
  pinMode (12,OUTPUT);
  pinMode (13,OUTPUT);
  
}

  int i=0;
  
void loop() {

  delay (1000);

  digitalWrite(10+i,LOW);

  i++;

  if(i==5){ 
    i=0;

    for(int j=0;j<4;j++)
      digitalWrite(10+j,HIGH);
    
  }

}
