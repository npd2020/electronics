
float napruga =0;
float napruga_fixed=0;
void setup() {
  #define led 5
  pinMode(7, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A7, INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  napruga =analogRead(A7);
  napruga_fixed = map(napruga,0,1023,7,11);
  constrain(napruga_fixed, 7,11);
  Serial.println(napruga_fixed);
  for(int i=7;i<12;i++){
   if (i==napruga_fixed){
  digitalWrite(i,HIGH);
  }
  else{
    digitalWrite(i,LOW);
  }
  delay(30);
  
}}
