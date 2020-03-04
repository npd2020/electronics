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
    digitalWrite (i,LOW);
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
    case 3:
      digitalWrite (4,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (8,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 4:
      digitalWrite (3,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 5:
      digitalWrite (3,HIGH);
      digitalWrite (4,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (8,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 6:
      digitalWrite (3,HIGH);
      digitalWrite (4,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (7,HIGH);
      digitalWrite (8,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 7:
      digitalWrite (4,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 8:
      digitalWrite (3,HIGH);
      digitalWrite (4,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (7,HIGH);
      digitalWrite (8,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 9:
      digitalWrite (3,HIGH);
      digitalWrite (4,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (6,HIGH);
      digitalWrite (8,HIGH);
      digitalWrite (9,HIGH);
      break;
    case 0:
      digitalWrite (3,HIGH);
      digitalWrite (4,HIGH);
      digitalWrite (5,HIGH);
      digitalWrite (7,HIGH);
      digitalWrite (8,HIGH);
      digitalWrite (9,HIGH);  
      break;
  }
     
}


void loop() {
  
 int q = analogRead (1);

  q = map(q,900, 1023,0,9);
  number (q);
 
 delay(200);
 
  
}
