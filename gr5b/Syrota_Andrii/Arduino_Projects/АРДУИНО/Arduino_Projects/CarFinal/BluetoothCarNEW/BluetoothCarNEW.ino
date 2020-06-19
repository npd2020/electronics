#define BT_TX 9
#define BT_RX 8
#define PARSE_AMOUNT 4         // число значений в массиве, который хотим получить

int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
int dataX, dataY,dataZ, dataK;
unsigned long last_time=0;
int value1, value2;


#include <AltSoftSerial.h>//!ОБЯЗАТЕЛЬНО подключать HC-06 вот так RXD-D9 TXD-D8 D10 unusable
AltSoftSerial mySerial;




void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  servo1.attach(5);
  servo2.attach(6);
}

void loop() {
  parsing();              // функция парсинга
  if (recievedFlag) {     // если получены данные
    recievedFlag = false;
    dataX = intData[0];
    dataY = intData[1];
    dataZ = intData[2];
    dataK = intData[3];
    /*for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
      Serial.print(intData[i]); Serial.print(" ");
      } Serial.println();*/
    Serial.print(dataX);
    Serial.print(" ");
    Serial.print(dataY);
    Serial.print(" ");
    Serial.print(dataZ);
    Serial.print(" ");
    Serial.println(dataK);
  }

if(millis()-last_time>25){       // waits for the servo to get there
    value1=map(dataZ,-40,40,750,2250);     //переносимо вхідні дані в діапазон ШИМ
    value2=map(dataK,-40,40,750,2250);
     servo1.write(value1); 
     servo2.write(value2); 
     last_time=millis();}
}

boolean getStarted;
byte index;
String string_convert = "";
void parsing() {
  if (mySerial.available() > 0) {
    char incomingByte = mySerial.read();        // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != ' ' && incomingByte != ';') {   // если это не пробел И не конец
        string_convert += incomingByte;       // складываем в строку
      } else {                                // если это пробел или ; конец пакета
        intData[index] = string_convert.toInt();  // преобразуем строку в int и кладём в массив
        string_convert = "";                  // очищаем строку
        index++;                              // переходим к парсингу следующего элемента массива
      }
    }
    if (incomingByte == '$') {                // если это $
      getStarted = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку
    }
    if (incomingByte == ';') {                // если таки приняли ; - конец парсинга
      getStarted = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
    }
  }
}
