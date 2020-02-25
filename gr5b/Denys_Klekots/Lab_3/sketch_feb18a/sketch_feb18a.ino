void setup() {

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);

  
}

void number (int n){

  digitalWrite (10,HIGH);

  for(int i=2;i<10;i++){
    digitalWrite (10,HIGH);
  }
  
  switch (n){
    
    case 1:
      digitalWrite (5,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 2:
      digitalWrite (4,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (7,HIGH);
      digitalWrite (8,HIGH);
      break;
  }
  
  
   
}


void loop() {
  
  number(1);
  
}
