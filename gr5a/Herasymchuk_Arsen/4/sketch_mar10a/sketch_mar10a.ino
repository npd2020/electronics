#include <SPI.h>
#include <Adafruit_GFX.h>

#include <Max72xxPanel.h>

int pinCS = 9;
int numberOfHorizontalDisplays = 1; 
int numberOfVerticalDisplays = 1; 

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
    matrix.setIntensity(4); 
 
}
 int a1=2;
  int a2=2;
  int a3=2;
  int a4=5;
  int a5=5;
  int a6=5;
  int a7=4;
  int a8=5;
  int a9=6;
  int a10=1;
  int a11=2;
  int a12=3;
  int j=0;

void A(){
  a1=a1+1;
  if(a1<=7)  matrix.drawPixel(a1, 1, HIGH);
  if(a1>7){
     a1=0;
    matrix.drawPixel(a1, 1, HIGH);
  }
  a2=a2+1;
  if(a2<=7)  matrix.drawPixel(a2, 2, HIGH);
  if(a2>7){
     a2=0;
    matrix.drawPixel(a2, 2, HIGH);
  }
  a3=a3+1;
  if(a3<=7)  matrix.drawPixel(a3, 3, HIGH);
  if(a3>7){
     a3=0;
    matrix.drawPixel(a3, 3, HIGH);
  }
  a4=a4+1;
  if(a4<=7)  matrix.drawPixel(a4, 1, HIGH);
  if(a4>7){
     a4=0;
    matrix.drawPixel(a4, 1, HIGH);
  }
  a5=a5+1;
  if(a5<=7)  matrix.drawPixel(a5, 2, HIGH);
  if(a5>7){
     a5=0;
    matrix.drawPixel(a5, 2, HIGH);
  }
  a6=a6+1;
  if(a6<=7)  matrix.drawPixel(a6, 3, HIGH);
  if(a6>7){
     a6=0;
    matrix.drawPixel(a6, 3, HIGH);
  }
 a7=a7+1;
  if(a7<=7)  matrix.drawPixel(a7, 6, HIGH);
  if(a7>7){
     a7=0;
    matrix.drawPixel(a7, 6, HIGH);
  }
   a8=a8+1;
  if(a8<=7)  matrix.drawPixel(a8, 6, HIGH);
  if(a8>7){
     a8=0;
    matrix.drawPixel(a8, 6, HIGH);
  }
 a9=a9+1;
  if(a9<=7)  matrix.drawPixel(a9, 5, HIGH);
  if(a9>7){
     a9=0;
    matrix.drawPixel(a9, 5, HIGH);
  }
 a10=a10+1;
  if(a10<=7)  matrix.drawPixel(a10, 5, HIGH);
  if(a10>7){
     a10=0;
    matrix.drawPixel(a10, 5, HIGH);
  }
   a11=a11+1;
  if(a11<=7)  matrix.drawPixel(a11, 6, HIGH);
  if(a11>7){
     a11=0;
    matrix.drawPixel(a11, 6, HIGH);
  }
   a12=a12+1;
  if(a12<=7)  matrix.drawPixel(a12, 6, HIGH);
  if(a12>7){
     a12=0;
    matrix.drawPixel(a12, 6, HIGH);
  }
}
void B(){
  matrix.drawPixel(a1, 1, LOW);
  matrix.drawPixel(a2, 2, LOW);
  matrix.drawPixel(a3, 3, LOW);
  matrix.drawPixel(a4, 1, LOW);
  matrix.drawPixel(a5, 2, LOW);
  matrix.drawPixel(a6, 3, LOW);
  matrix.drawPixel(a7, 6, LOW);
  matrix.drawPixel(a8, 6, LOW);
  matrix.drawPixel(a9, 5, LOW);  
  matrix.drawPixel(a10, 5, LOW);
  matrix.drawPixel(a11, 6, LOW);
  matrix.drawPixel(a12, 6, LOW);

}

void loop() {  
  A();    
    matrix.write();
    delay(300);
   B();
     matrix.write();
    delay(100);
    }
