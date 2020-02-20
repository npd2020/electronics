void setup() {

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);


  
}

int i=0;


void loop() {

 if(i==4){

  delay(1000);
  
  i=0;

  for(int j=0;j<4;j++)
    digitalWrite(8+j,LOW);
  }
    
   digitalWrite(8+i,HIGH);

  delay(100);
  
  i++;
  
}
