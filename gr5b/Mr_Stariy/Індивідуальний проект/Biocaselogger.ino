#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <Wire.h>
#include <DHT.h>
#include <BMP085.h>
File myFile;
const uint8_t PIN_CS = 10; // указываем номер вывода arduino подключенного к выводу CS адаптера
DS3231 Clock;
DHT dht;               // Объявление переменной класса dht11
BMP085 dps = BMP085();

bool Century = false;
bool h12;
bool PM;
byte year, month, date, DoW, hour, minute, second;
long Temperature = 0, Pressure = 0;

void setup(){
    Serial.begin(9600);
    Wire.begin();
    delay(1000);

    if(!SD.begin(PIN_CS)){                           // инициализация SD карты с указанием номера вывода CS
    Serial.println("SD-card not found"); return;   // ошибка инициализации. карта не обнаружена или не подключён (неправильно подключён) адаптер карт MicroSD
  }    

    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);

    dht.setup(4); // data pin 4
    
    digitalWrite(3, LOW);     // устновка на 0 
    digitalWrite(6, HIGH);    // устновка на 0 
    digitalWrite(5, HIGH);    // устновка на 0 
    
// Start the I2C interface
// Clock.setSecond(0);//Set the second 
// Clock.setMinute(42);//Set the minute 
// Clock.setHour(12); //Set the hour 
// Clock.setDoW(5); //Set the day of the week
// Clock.setDate(13); //Set the date of the month
// Clock.setMonth(7); //Set the month of the year
// Clock.setYear(18); //Set the year (Last two digits of the year)

dps.init(MODE_STANDARD, 98000, false);
//980mbar*100=98000Pa

  } 

void loop() {
  
  int i = 0;
   
  String filename;
  static unsigned int number;
    if (number <= 9) filename = "d0000";    
    if (number > 9 && number <= 99) filename = "d000";
    if (number > 99 && number <= 999) filename = "d00";
    if (number > 999 && number <= 9999) filename = "d0";
    if (number > 9999 && number <= 99999) filename = "d";    
    filename +=  number++;
    filename += ".txt";
    
    File myFile = SD.open(filename, FILE_WRITE);   
    
  do
  { 
  byte second, minute, hour, date, month, year;
  second = Clock.getSecond();
  minute = Clock.getMinute();
  hour = Clock.getHour(h12, PM);
  date = Clock.getDate();
  month = Clock.getMonth(Century);
  year = Clock.getYear();

 myFile.print("20");
 myFile.print(year,DEC); 
 myFile.print('-');
 myFile.print(month,DEC);
 myFile.print('-');
 myFile.print(date,DEC);
 myFile.print(' ');
 myFile.print(hour,DEC);
 myFile.print(':');
 myFile.print(minute,DEC);
 myFile.print(':');
 myFile.print(second,DEC);
 myFile.print(' ');
 myFile.print(Clock.getTemperature()); 
 myFile.print(' ');

  dps.getPressure(&Pressure);
  dps.getTemperature(&Temperature);

  myFile.print(Pressure/133.3);
  myFile.print(' ');
  myFile.print(Temperature*0.1);
  myFile.print(' ');
  
delay(dht.getMinimumSamplingPeriod());
 myFile.print(dht.getHumidity());
 myFile.print(' ');
 myFile.println(dht.getTemperature());
 
// работаем с реле
digitalWrite(3, HIGH);   // зажигаем подсветку, термометр, 
digitalWrite(5, LOW);   // нажимаем включение фотоаппарата
delay(1000);              // ждем время нажима 
digitalWrite(5, HIGH);    // заканчиваем нажим
delay(10000);              // ждем 10 секунд
digitalWrite(6, LOW);   // нажимаем спуск фотоаппарата
delay(1000);              // ждем время нажима
digitalWrite(6, HIGH);    // заканчимаем нажим
delay(4000);             //4 секунд пауза 
digitalWrite(3, LOW);    // выключакм подсветку термометр

//blink LED to indicate activity
int k = 1;
do
{
  digitalWrite(8, HIGH);   // зажигаем светодиод
  delay(1000);              // ждем секунду
  digitalWrite(8, LOW);    // выключаем светодиод
  delay(1000);              // ждем секунду
k++;   
  }  while (k < 299); // 1 час между экспозициями  (-16 сек)

i++;
  }  while (i < 144);   // сколько позиций в файле
  
myFile.close();  // закрытие файла 

  do {
   i=i-i; 
    }  while (i = 0);
}

