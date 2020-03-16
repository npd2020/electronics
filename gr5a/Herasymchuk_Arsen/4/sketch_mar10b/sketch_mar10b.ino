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
 int a1=0;
 int a2=0;

void loop() {  
  if((a1==7)&&(a2<7)) {matrix.drawPixel(a1, a2, HIGH);
     matrix.write();
    delay(300);
    matrix.drawPixel(a1, a2, LOW);
     matrix.write();
    delay(100);
    a2=a2+1;
  }
  if((a1>0)&&(a2==7)) {matrix.drawPixel(a1, a2, HIGH);
   matrix.write();
    delay(300);
    matrix.drawPixel(a1, a2, LOW);
     matrix.write();
    delay(100);
    a1=a1-1;
  }
  if((a1==0)&&(a2>0)) {matrix.drawPixel(a1, a2, HIGH);
   matrix.write();
    delay(300);
    matrix.drawPixel(a1, a2, LOW);
     matrix.write();
    delay(100);
    a2=a2-1;
  }
 if((a1<7)&&(a2==0)) {matrix.drawPixel(a1, a2, HIGH);
  matrix.write();
    delay(300);
    matrix.drawPixel(a1, a2, LOW);
     matrix.write();
    delay(100);
    a1=a1+1;
  }   
}
