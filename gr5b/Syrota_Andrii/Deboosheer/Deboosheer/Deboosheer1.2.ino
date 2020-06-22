#include <ServoTimer2.h>  //подключена эта библиотека что бы не было конфликтов с timer 1 (который использует AltsoftSerial.h), отключен ШИМ на пинах D3, D11

#define pin_osnova 10   // пин, к которому подключена серво-основа
#define pin_hvat   11   // пин подключения хваталки
#define pin_short  A2   // пин, к которому подключена короткая балка
#define pin_long   13   // пин, к которому подключена длинная балка

ServoTimer2 servo_long;   // с длинной балкой
ServoTimer2 servo_short;  // с короткой балкой балкой
ServoTimer2 servo_osnova; // основа
ServoTimer2 servo_hvat;   // сама хваталка



#include <GyverMotor.h> //библиотека управления моторами

#define MOTOR_MAX 255   // максимальный сигнал на мотор (max 255)
#define IN1 4           //выходы с драйвера моторов
#define IN2 5           // IN2 обязательно должен быть ШИМ пином 
#define IN3 7  
#define IN4 6           // IN4 обязательно должен быть ШИМ пином

GMotor motorL(IN1, IN2);
GMotor motorR(IN3, IN4);




#include <AltSoftSerial.h> //!ОБЯЗАТЕЛЬНО подключать HC-06 вот так RXD-D9 TXD-D8 ШИМ на D10 отключен 
#define BT_TX 9            //пины на подключение блютузмодуля HC-06
#define BT_RX 8            //пины на подключение блютузмодуля HC-06
AltSoftSerial mySerial;




#include <Wire.h>                  //библиотека подключения к I2c
#include <LiquidCrystal_I2C.h>     //библиотека управления ЛСД дисплеем 1602
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display



#define PARSE_AMOUNT 6         // число значений в массиве, который хотим получить
#define JOY_MAX 40             // рабочий ход джойстика (из приложения)
int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
int dutyR, dutyL;
int signalX, signalY;
int dataX, dataY;

int data_osnova_new=17, data_osnova_old; // переменные для серво new и old для реализации задержек (что бы не так быстро крутилась) 
int data_long = 40;
int data_short =15; 
int data_hvat;//хват без нью олд , потому что ему не нужны задержки
unsigned long last_time_osnova=0;
unsigned long last_time_others=0;

unsigned long last_time_LCD=0; // используется с миллис (для задержки вывода на дисплей)
unsigned long lastflash;      // запоминание времени оборота колеса
volatile int RPM;             // ОБ/мин




void setup() {
  Serial.begin(9600);
  
  mySerial.begin(9600);  // метод библиотеки ALTsoftserial
 
  servo_long.attach(pin_long);
  servo_short.attach(pin_short);              // аналоговые пины с сервами работают тоже
  servo_osnova.attach(pin_osnova);
  servo_hvat.attach(pin_hvat);

  data_osnova_old=map(data_osnova_new,0,40,750,2250);
  data_long=map(data_long,0,40,750,2250);
  data_short=map(data_short,0,40,750,2250);
  
  servo_osnova.write(data_osnova_old); //установка начального положения основы
  servo_long.write(data_long);     //установка начального положения длинной балки
  servo_short.write(data_short);   //установка начального положения короткой балки
  
  lcd.init();                      // Print a message to the LCD.
  lcd.backlight();                 //Инициализация подсветки
  lcd.setCursor(5,1);              
  lcd.print("RPM");                // надпись RPM (обороты в минуту)
  
  attachInterrupt(0,sens,RISING);  //подключить прерывание на 2 пин при повышении сигнала
}


void loop() {
  
//тахометp
  if ((millis()-lastflash)>1000){   //если сигнала нет больше секунды
    RPM=0;                          //считаем что RPM 0
  }

  if(millis()-last_time_LCD>250){   //вывод значений тахометра на дисплей 
      if(RPM <10){
    lcd.setCursor(1,1); 
    lcd.print("  ");          
      }
      else if (9<RPM<99){           //if и else if для очистки дисплея от паразитных старых значений
    lcd.setCursor(2,1);  
    lcd.print(" ");    
      }
  lcd.setCursor(0,1);               //ставим курсор на нулевое положение уже очищеной строки 
  lcd.print(RPM);
  last_time_LCD=millis();
  }
  

  parsing();                // функция парсинга
  if (recievedFlag) {       // если получены данные
    recievedFlag = false;
    dataX = intData[0];  //Х данные для колес
    dataY = intData[1];  //У данные для колес
 //данные для сервоприводов :  
    data_osnova_new = map(intData[2], 0, 40, 750, 2250); 
    data_long   = map(intData[3], 0, 40, 750, 2250); 
    data_short  = map(intData[4], 0, 40, 750, 2250);  
    data_hvat   = map(intData[5], 0, 40, 750, 2250); 
  }

if(millis()-last_time_osnova>10){       // ждет 4 мс что бы серва сделала маленький шажок
  if(data_osnova_new > data_osnova_old && abs(data_osnova_new - data_osnova_old)>8){//реализация задержек основы  
   data_osnova_old=data_osnova_old+8;
  } 
  if(data_osnova_new <data_osnova_old && abs(data_osnova_new - data_osnova_old)>8){  
   data_osnova_old=data_osnova_old-8;
  } 
   servo_osnova.write(data_osnova_old); 
   last_time_osnova=millis();
     }

 if(millis()-last_time_others>25){       // ждет 4 мс что бы серва сделала маленький шажок
   servo_long.write(data_long); 
   servo_short.write(data_short); 
   servo_hvat.write(data_hvat); 
   last_time_others=millis();
     }




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
void parsing() {           //функция parsing разбивает этот пакет вида $valueX valueY и тд.; в массив intData               
  if (mySerial.available() > 0) {
    char incomingByte = mySerial.read();      // обязательно ЧИТАЕМ входящий символ
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

void sens() {                                 //функция дающая значения на тахометр
  RPM=60/((float)(millis()-lastflash)/1000);  //расчет
  lastflash=millis();                         //запомнить время последнего оборота
}
