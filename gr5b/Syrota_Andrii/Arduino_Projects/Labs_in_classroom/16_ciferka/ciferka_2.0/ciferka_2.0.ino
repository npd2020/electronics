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
  Serial.println(napruga_fixed);
  if(napruga_fixed=0){
    for(int i=1;i<9;i++)  digitalWrite(i,HIGH);
    digitalWrite(5,LOW);
    delay(1000);
 }
  if(napruga_fixed=1){
 }
  if(napruga_fixed=2){
 }
  if(napruga_fixed=3){
 }
  if(napruga_fixed=4){
 }
  if(napruga_fixed=5){
 }
  if(napruga_fixed=6){
 }
  if(napruga_fixed=7){
 }
  if(napruga_fixed=8){
    //for(int i=1;i<9;i++)  digitalWrite(i,HIGH);
 }
  if(napruga_fixed=9){
 }
  if(napruga_fixed=10){
 }
  if(napruga_fixed=11){
 }
  if(napruga_fixed=12){
 }
  if(napruga_fixed=13){
 }
  if(napruga_fixed=14){
 }
  if(napruga_fixed=15){
 }
 //delay(100);
 //for(int i=2;i<9;i++) digitalWrite(i,LOW);

}
