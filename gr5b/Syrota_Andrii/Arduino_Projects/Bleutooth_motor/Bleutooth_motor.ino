#define POWER 10//мотор
int val,pmw;//val=значення з bleutooth-модуля; pwm=ШИМ

void setup()
{
  Serial.begin(9600);
  pinMode(POWER, OUTPUT);
}

void loop()
{
  if (Serial.available())//при отриманні данних виконується:
  {
    val = Serial.read();//(0-9) вислані з телефону (згідно системі ASCII) приймаються як (48-57) 
    val=constrain(val,48,57);//обмежуємо вхідні дані
    pmw=map(val,48,57,0,250);//переносимо вхідні дані в діапазон ШИМ
    pmw=constrain(pmw,0,250);//обиежуємо діапазон ШИМ
    analogWrite(POWER, pmw); }//подаємо живлення на мотор
}
