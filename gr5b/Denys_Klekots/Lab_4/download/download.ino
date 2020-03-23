#include SPI.h
#include Adafruit_GFX.h
#include Max72xxPanel.h //бібліотека для роботи з драйвером світлодіодної матриці

int pinCS = 9;
int numberOfHorizontalDisplays = 1;  кількість матриць по горизонталі (в нас одна)
int numberOfVerticalDisplays = 1;  кількість матриць по ветрикалі (в нас одна)

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
    matrix.setIntensity(4);  яскравість от 0 до 15
}

void loop() {
    matrix.drawPixel(3, 4, HIGH);  вмикаємо світлодіод з координатами {3,4}
    matrix.write();  виводимо стан світлодіодів на матрицю
    delay(300);
    matrix.drawPixel(3, 4, LOW);  вимикаєто світлодіод
    matrix.write();
    delay(300);
}
