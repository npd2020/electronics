#include <ServoTimer2.h>
ServoTimer2 servo1;    // с длинной балкой
ServoTimer2 servo2;    // с короткой балкой балкой
ServoTimer2 servo0;//основа
ServoTimer2 servoHvat; //сама хваталка

#define MOTOR_MAX 255  // максимальный сигнал на мотор (max 255)
#define JOY_MAX 40    // рабочий ход джойстика (из приложения)

#define IN1 4
#define IN2 5         // IN2 обязательно должен быть ШИМ пином!!!
#define IN3 7
#define IN4 6        // IN4 обязательно должен быть ШИМ пином!!!

#define BT_TX 9
#define BT_RX 8
#define S_0 10         //пин, к которому подключена серво-основа
#define pin_hvat 11     // пин подключения хваталки
#define hvat_min 750
#define hvat_max 1700


/*
  Bluetooth шлёт пакет вида $valueX valueY;
  моя функция parsing разбивает этот пакет в массив intData
  Парсинг полностью прозрачный, не блокирующий и с защитой от битого пакета,
  так как присутствует строгий синтаксис посылки. Без хешсуммы конечно, но и так норм
*/
#define PARSE_AMOUNT 6         // число значений в массиве, который хотим получить

int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
int dutyR, dutyL;
int signalX, signalY;
int dataX, dataY,dataX1,dataY1,dataZ, dataHvat;
int value1, value2;//сигнал на сервы
unsigned long last_time=0;

unsigned long last_time_LCD=0;//используется с миллис (для задержки вывода на дисплей)

unsigned long lastflash;//запоминание времени оборота колеса
volatile int RPM;//ОБ/мин





#include "GyverMotor.h"
GMotor motorL(IN1, IN2);
GMotor motorR(IN3, IN4);

#include <AltSoftSerial.h>//!ОБЯЗАТЕЛЬНО подключать HC-06 вот так RXD-D9 TXD-D8 D10 unusable
AltSoftSerial mySerial;

#include <Wire.h> //библиотека подключения к I2c
#include <LiquidCrystal_I2C.h> //библиотека управления ЛСД дисплеем 1602
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  Serial.begin(9600);
  
  mySerial.begin(9600);// метод библиотеки ALTsoftserial
 
  servo1.attach(13);
  servo2.attach(A2);// подключил на А0 с целью теста, работает отлично!
  servo0.attach(S_0);
  servoHvat.attach(pin_hvat);
  lcd.init();  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(5,1);
  lcd.print("RPM"); // надпись РМП (обороты в минуту)
  attachInterrupt(0,sens,RISING); //подключить прерывание на 2 пин при повышении сигнала
  servo1.write(2250);
  servo2.write(1050);
  servo0.write(1500);
}


void loop() {
//тахометр

  if ((millis()-lastflash)>1000){ //если сигнала нет больше секунды
    RPM=0;  //считаем что RPM 0
  }

 //вывод значений тахометра на дисплей 
  if(millis()-last_time_LCD>250){
      if(RPM <10){
    lcd.setCursor(1,1); 
    lcd.print("  ");          
      }
      else if (9<RPM<99){//if и else if для очистки дисплея от паразитных старых значений
    lcd.setCursor(2,1);  
    lcd.print(" ");    
      }
  lcd.setCursor(0,1); //ставим курсор на нулевое положение уже очищеной строки 
  lcd.print(RPM);
  last_time_LCD=millis();
  }
  

  parsing();              // функция парсинга
  if (recievedFlag) {     // если получены данные
    recievedFlag = false;
    dataX = intData[0];
    dataY = intData[1];
    dataX1 = intData[2];
    dataY1=intData[3];
    dataZ = intData[4];
    dataHvat=intData[5];
    
    for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
      Serial.print(intData[i]);
      Serial.print(" ");
      }
    Serial.println();
    Serial.print(dataX);
    Serial.print(" ");
    Serial.print(dataY);
    Serial.print(" ");

    Serial.print(" ");
    Serial.print(map(dataX1,0,40,750,2250));
    Serial.print(" ");
    Serial.println(map(dataHvat,0,40,hvat_min,hvat_max));
  }

if(millis()-last_time>35){       // waits for the servo to get there  
    servo0.write(map(dataX1,0,40,750,2250));
    servo1.write(map(dataY1,0,40,750,2250));
    servo2.write(map(dataZ,0,40,750,2250));
    servoHvat.write(map(dataHvat,0,40,750,2250));
     last_time=millis();}


  if (dataX == 0 && dataY == 0) {   // если мы в "мёртвой" зоне
    motorR.setMode(STOP);           // не двигаемся
    motorL.setMode(STOP);
    dutyR = 0;
    dutyL = dutyR;
  } else {
    signalY = map((dataY), -JOY_MAX, JOY_MAX, -MOTOR_MAX, MOTOR_MAX);         // сигнал по У
    signalX = map((dataX), -JOY_MAX, JOY_MAX, -MOTOR_MAX / 2, MOTOR_MAX / 2); // сигнал по Х

    dutyR = signalY + signalX;
    dutyL = signalY - signalX;

    if (dutyR > 0) motorR.setMode(FORWARD);
    else motorR.setMode(BACKWARD);

    if (dutyL > 0) motorL.setMode(FORWARD);
    else motorL.setMode(BACKWARD);

    dutyR = constrain(abs(dutyR), 0, MOTOR_MAX);
    dutyL = constrain(abs(dutyL), 0, MOTOR_MAX);
  }
  motorR.setSpeed(dutyR);
  motorL.setSpeed(dutyL);
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

void sens() {//функция дающая значения на тахометр
  RPM=60/((float)(millis()-lastflash)/1000);  //расчет
  lastflash=millis();  //запомнить время последнего оборота
}
