int ledPin1 = 10;                // світлодіод 1
int ledPin2 = 11;                // світлодіод 2
int ledPin3 = 12;                // світлодіод 3
int btnPin1 = 15;                // кнопка 1      //кнопки підключенні до цифрових портів 15-17
int btnPin2 = 16;                // кнопка 2      //
int btnPin3 = 17;                // кнопка 3      //
int val1=0;
int val2=0;
int val3=0;

void setup()                     
{
  pinMode(ledPin1, OUTPUT);      // вихід світлодіода
  pinMode(btnPin1, INPUT);       // вихід кнопки
  pinMode(ledPin2, OUTPUT);      // вихід світлодіода
  pinMode(btnPin2, INPUT);       // вихід кнопки
  pinMode(ledPin3, OUTPUT);      // вихід світлодіода
  pinMode(btnPin3, INPUT);       // вихід кнопки
  pinMode(13,OUTPUT);
  digitalWrite (13,HIGH);

}

void loop()                      
{
  val1 = digitalRead(btnPin1);    // взнаєм стан кнопки
  val2 = digitalRead(btnPin2);    // взнаєм стан кнопки
  val3 = digitalRead(btnPin3);    // взнаєм стан кнопки
  if(val1==HIGH)                 // кнопка натиснута
  {
    digitalWrite(ledPin1, HIGH); // вмикаємо світлодіод
  }
  else                          // кнопка не натиснута
  {
    digitalWrite(ledPin1, LOW);  // вимикаємо світлодіод
  }
  
  if(val2==HIGH)                 // кнопка натиснута
  {
    digitalWrite(ledPin2, HIGH); // вмикаємо світлодіод
  }
  else                          // кнопка не натиснута
  {
    digitalWrite(ledPin2, LOW);  // вимикаємо світлодіод
  }
 
  if(val3==HIGH)                 // кнопка натиснута
  {
    digitalWrite(ledPin3, HIGH); // вмикаємо світлодіод
  }
  else                          // кнопка не натиснута
  {
    digitalWrite(ledPin3, LOW);  // вимикаємо світлодіод
  }
  delay(100);
}
