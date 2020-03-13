#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 9;
int numberOfHorizontalDisplays = 1; // кількість матриць по горизонталі
int numberOfVerticalDisplays = 1; // кількість матриць по вертикалі

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const byte data[8] = {
    0b00111100,
    0b01000010,
    0b10100101,
    0b10000001,
    0b10100101,
    0b10011001,
    0b01000010,
    0b00111100
};    // зашифровані пікселі смайла

void setup() {
    matrix.setIntensity(7); // яскравість від 0 до 15

    matrix.fillScreen(LOW); // очищення матриці
    for ( int y = 0; y < 8; y++ ) {
        for ( int x = 0; x < 8; x++ ) {
            
            matrix.drawPixel(x, y, data[y] & (1<<x));  // запалюємо х-й піксель в у-й стрічці
        }
    }
    matrix.write(); // вивід пікселей на матрицю
}

void loop() {
}
