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
}
 
void loop()
{
  // определяем число, которое следует отобразить.
  //  Пусть им будет номер текущей секунды, зацикленный на десятке
  int number = (millis() / 1000) % 10;
  // получаем код из массива, в котором содержится полученная цифра
  int mask = numberSegments[number];
  // для каждого из 7 сегментов индикатора
  for (int i = 0; i < SEGMENT_COUNT; ++i) {
    // определяем: должен ли он быть включён.
    boolean enableSegment = bitRead(mask, i);
    // включаем/выключаем сегмент на основе полученного значения
    digitalWrite(i + FIRST_SEGMENT_PIN, enableSegment);
  }
}
