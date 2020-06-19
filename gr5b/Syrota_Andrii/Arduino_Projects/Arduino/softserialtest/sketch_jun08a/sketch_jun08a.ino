#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX*/
 
void setup()  
{
  // Инициализируем последовательный интерфейс и ждем открытия порта:
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
 
  // устанавливаем скорость передачи данных для последовательного порта, созданного 
  // библиотекой SoftwareSerial
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}
 
void loop() // выполняется циклически
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
