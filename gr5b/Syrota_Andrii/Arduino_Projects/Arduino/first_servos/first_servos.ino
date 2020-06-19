#include <AltSoftSerial.h>

AltSoftSerial mySerial;

#include <ServoTimer2.h>
ServoTimer2 SERV;
/*#define CLK 2//повороти
#define DT 3//повороти
#define SW 4//кнопка енкодера*/

/*#include <Servo.h>
Servo SERV;*/
/*#include <GyverEncoder.h>//бібліотека під енкодер*/


/*#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // TX, RX*/

//Encoder enc(CLK, DT, SW);енкодер в режимі поворот+кнопка
//Servo myservo1;   create servo object to control a servo


int val=0;//дані з енкодера
int bleu;//дані з блютуз
byte pwm1,pwm2;//ШИМ який піде на світлодіод
unsigned long last_time=0;
 


void setup() {

   mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
 mySerial.println("Hello, world?");
  /*enc.setType(TYPE2);//тип енкодера (2 сигнала за один такт повороту)
  enc.setDirection(REVERSE);//лівий поворот=правий і навпаки
  */SERV.attach(3);  // attaches the servo on pin 9 to the servo object
 
}

void loop() {
  SERV.write(950);
  /*enc.tick();
  if (enc.isTurn()){//якщо відбувся поворот
    if (enc.isRight())  val+=5;//поворот на 1 поділку(повільний)
    if (enc.isLeft()) val-=5;
    if (enc.isFastR())  val+=20;//поворот на 1 поділку(швидкий)
    if (enc.isFastL()) val-=20;*/

 /* val=constrain(val,-100,100);     //межі енкодера
    pwm1=map(val,-100,100,0,180);
    pwm1=constrain(pwm1,0,180);      
    myservo1.write(pwm1); */             // sets the servo position according to the scaled value

//if(millis()-last_time>25){       // waits for the servo to get there
 if (mySerial.available()>0)//при отриманні данних виконується:
     Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
    //bleu = btSerial.read();//(0-9) вислані з телефону (згідно системі ASCII) приймаються як (48-57) 
    //bleu=constrain(bleu,48,57);    //обмежуємо вхідні дані
    //pwm2=map(bleu,48,57,0,180);     //переносимо вхідні дані в діапазон ШИМ
    //pwm2=constrain(pwm2,0,180);     //обиежуємо діапазон ШИМ
    //myservo2.write(pwm2);
   //}    
  //  last_time=millis();}
}
