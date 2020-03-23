/*
 * LED with button 3 кнопки управляет тремя светодиодами
 */

int ledPin1 = 10;                // сетодиод 1
int ledPin2 = 11;                // сетодиод 2
int ledPin3 = 12;                // сетодиод 3
int btnPin1 = 15;                // кнопка 1
int btnPin2 = 16;                // кнопка 2
int btnPin3 = 17;                // кнопка 3
int val1=0;
int val2=0;
int val3=0;

void setup()                     
{
  pinMode(ledPin1, OUTPUT);      // это выход - светодиод
  pinMode(btnPin1, INPUT);       // а это вход - кнопка
  pinMode(ledPin2, OUTPUT);      // это выход - светодиод
  pinMode(btnPin2, INPUT);       // а это вход - кнопка
  pinMode(ledPin3, OUTPUT);      // это выход - светодиод
  pinMode(btnPin3, INPUT);       // а это вход - кнопка
  pinMode(13,OUTPUT);
  digitalWrite (13,HIGH);

}

void loop()                      
{
  val1 = digitalRead(btnPin1);    // узнаём состояние кнопки
  val2 = digitalRead(btnPin2);    // узнаём состояние кнопки
  val3 = digitalRead(btnPin3);    // узнаём состояние кнопки
  if(val1==HIGH)                 // кнопка нажата
  {
    digitalWrite(ledPin1, HIGH); // зажигаем светодиод
  }
  else                          // кнопка не нажата
  {
    digitalWrite(ledPin1, LOW);  // гасим светодиод
  }
  
  if(val2==HIGH)                 // кнопка нажата
  {
    digitalWrite(ledPin2, HIGH); // зажигаем светодиод
  }
  else                          // кнопка не нажата
  {
    digitalWrite(ledPin2, LOW);  // гасим светодиод
  }
 
  if(val3==HIGH)                 // кнопка нажата
  {
    digitalWrite(ledPin3, HIGH); // зажигаем светодиод
  }
  else                          // кнопка не нажата
  {
    digitalWrite(ledPin3, LOW);  // гасим светодиод
  }
  delay(100);
}
