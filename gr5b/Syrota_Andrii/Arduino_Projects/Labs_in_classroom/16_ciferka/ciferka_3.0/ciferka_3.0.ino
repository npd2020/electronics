float napruga;
int napruga_fixed;
void setup() {
  pinMode(A7,INPUT);
  for(int i=2; i<9;i++) pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop() {
   napruga =analogRead(A7);
  //napruga_fixed = map(napruga,0,1023,0,16);
  //constrain(napruga_fixed,0,16);
  //Serial.println(napruga_fixed);
 
  napruga_fixed=0;
  switch(napruga_fixed){
    case 0: for(int i=2; i<9,i!=5;i++) digitalWrite(i,HIGH);
            digitalWrite(5,LOW);
    case 1:;
    case 2: ;
    case 3: ;
    case 4: ;
    case 5: ;
    case 6: ;
    case 7: ;
    case 8:; 
    case 9: ;
    case 10: ;
    case 11: ;
    case 12: ;
    case 13: ;
    case 14: ;
    case 15: ;
  }

}
