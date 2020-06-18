#define FIRST_SEGMENT_PIN   1
#define SEGMENT_COUNT       8

// Всего цифр 10, поэтому в массиве 10 чисел.
byte numberSegments[10] = {
  0b01110111, 
  0b00010100, 
  0b10110011, 
  0b10110110, 
  0b11010100, 
  0b11100110, 
  0b11100111, 
  0b00110100, 
  0b11110111,
  0b11110110,
};
 
void setup()
{
  for (int i = 0; i < SEGMENT_COUNT; ++i)
    pinMode(i + FIRST_SEGMENT_PIN, OUTPUT);
    //Serial.begin(9600);
}
 
void loop()
{
  delay(500);
  //Serial.println(analogRead(A0));
  //  Пусть им будет номер текущей секунды, зацикленный на десятке
  int number = round(10-analogRead(A0)*10/1023);
  // получаем код из массива, в котором содержится полученная цифра
  int mask = numberSegments[number];
  // для каждого из 7 сегментов индикатора
 
  for (int i = 0; i < SEGMENT_COUNT+1; ++i) {
    // определяем: должен ли он быть включён.
    boolean enableSegment = bitRead(mask, i);
    // включаем/выключаем сегмент на основе полученного значения
    digitalWrite(i + FIRST_SEGMENT_PIN, enableSegment);
  }
}
