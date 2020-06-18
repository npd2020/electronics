#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h> //бібліотека для роботи з драйвером світлодіодної матриці
#define time 1000
#define size 4

int pinCS = 9;
int numberOfHorizontalDisplays = 1; // кількість матриць по горизонталі
int numberOfVerticalDisplays = 1;   // кількість матриць по вертикалі

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
    matrix.setIntensity(1); // яскравість від 0 до 15
}

void loop() {

    for(int k=0;k<64;k++){

        if(k<size)//В кінці матриці світлодіоди ми маємо вимикати світлодіоди
          matrix.drawPixel((64+k-size)%8, (64+k-size)/8, LOW);
            
        matrix.drawPixel(k%8, k/8, HIGH);//Всмкаємо потрібні світлодіоди
        matrix.drawPixel((k-size)%8, (k-size)/8, LOW);//Вимикаєм непотрібні світлодіоди
        matrix.write();      
        delay(time);

    }
}
