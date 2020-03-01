void setup() {

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);


  
}

int i=0;


void loop() {

 if(i==4){

  delay(1000);
  
  i=0;

  for(int j=0;j<4;j++)
    digitalWrite(2+j,LOW);
  }
    
   digitalWrite(2+i,HIGH);

  delay(100);
  
  i++;
  
}
