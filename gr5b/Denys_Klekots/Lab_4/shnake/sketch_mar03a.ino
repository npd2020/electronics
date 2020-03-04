#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#define time 4
#define size 4

int pinCS = 9;
int numberOfHorizontalDisplays = 1; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
    matrix.setIntensity(1); // яркость от 0 до 15
}

void loop() {

    for(int k=0;k<64;k++){

        if(k<size)
          matrix.drawPixel((64+k-size)%8, (64+k-size)/8, LOW);
            
        matrix.drawPixel(k%8, k/8, HIGH);
        matrix.drawPixel((k-size)%8, (k-size)/8, LOW);
        matrix.write();      
        delay(time);

    }
}
