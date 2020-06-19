#define CLK 2
#define DT 3
#define SW 4

# include <GyverEncoder.h>

Encoder enc(CLK, DT, SW);
int val=0;

void setup() {
  Serial.begin(9600);
  enc.setType(TYPE2);
  enc.setDirection(REVERSE);
}

void loop() {
  enc.tick();
  if (enc.isTurn()){
    if (enc.isRight())  val++;
    if (enc.isLeft()) val--;
    if (enc.isRightH())  val+=5;
    if (enc.isLeftH()) val-=5;
    if (enc.isFastR())  val+=10;
    if (enc.isFastL()) val-=10;
    Serial.println(val);
}
 if (enc.isClick()) Serial.println("click");
 if (enc.isHolded()) Serial.println("holded"); 
 if (enc.isDouble()) Serial.println("double");
 
}
