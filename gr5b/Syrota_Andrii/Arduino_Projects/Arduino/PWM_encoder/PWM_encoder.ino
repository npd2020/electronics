#define CLK 2//повороти
#define DT 3//повороти
#define SW 4//кнопка енкодера
#define svet 10//пін світлодіода

# include <GyverEncoder.h>//бібліотека під енкодер

Encoder enc(CLK, DT, SW);//енкодер в режимі поворот+кнопка

int val=0;//дані з енкодера
byte pwm,i,k;//ШИМ який піде на світлодіод


void setup() {
  Serial.begin(9600);
  enc.setType(TYPE2);//тип енкодера (2 сигнала за один такт повороту)
  enc.setDirection(REVERSE);//лівий поворот=правий і навпаки

}

void loop() {
  enc.tick();
  if (enc.isTurn()){//якщо відбувся поворот
    if (enc.isRight())  val+=5;//поворот на 1 поділку(повільний)
    if (enc.isLeft()) val-=5;
    if (enc.isFastR())  val+=20;//поворот на 1 поділку(швидкий)
    if (enc.isFastL()) val-=20;
    Serial.println(val);
}

  
 val=constrain(val,-100,100);//межі енкодера
 pwm=map(val,-100,100,0,255);
 pwm=constrain(pwm,0,255);//межі ШИМ
 
 if (enc.isClick()) {//якщо клацнута кнопка 
  if(pwm == 0) {//повністю включає або виключає на 1 сек.
    analogWrite(svet,255);
    delay(1000);}
  else {
    analogWrite(svet,0);
    delay(1000);}
 }
 
 if (enc.isHolded()) {//Виклик сигналу SOS, якщо кнопка затиснута
  analogWrite(svet,0);
  for(i=1;i<4;i++){
     analogWrite(svet,255);
     delay(250);
     analogWrite(svet,0);
     delay(250);}
  for(k=1;k<4;k++){
     analogWrite(svet,255);
     delay(1000);
     analogWrite(svet,0);
     delay(250);}  
  for(i=1;i<4;i++){
     analogWrite(svet,255);
     delay(250);
     analogWrite(svet,0);
     delay(250);}   
  } 
 
 analogWrite(svet,pwm);
}
