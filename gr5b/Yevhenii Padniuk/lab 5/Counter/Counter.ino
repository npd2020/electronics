// Визначаємо контакти зсувового регістру, застосовувані для семисегментного індикатора
#define LATCH_DIO 4 //налаштування для зсувового регістру
#define CLK_DIO 7 //налаштування для зсувового регістру
#define DATA_DIO 8 //налаштування для зсувового регістру

/* байти чисел від 0 до 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
/* Байт-карти для выбору десятку дисплея від 1 до 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};
 
void setup (){
 
/* налаштування для зсувового регістру */
pinMode(LATCH_DIO,OUTPUT);
pinMode(CLK_DIO,OUTPUT);
pinMode(DATA_DIO,OUTPUT);
}

void translateNumberToDigit(int numer){

WriteNumberToSegment(0 , numer%10);           //записуємо нульовий десяток
WriteNumberToSegment(1 , (numer%100)/10);     //записуємо перший десяток
WriteNumberToSegment(2 , (numer%1000)/100);   //записуємо другий десяток
WriteNumberToSegment(3 , (numer%10000)/1000); //записуємо третій десяток
  
}

int resistance;
 
void loop(){
  resistance=analogRead(0);//потенціометр підєднанй до 0-го аналового виходу
  
  resistance=map(resistance,0,1023,0,1000);//конвертуємо значення опору
  
  translateNumberToDigit(resistance);//виводимо значення опору на індикатор
}
 
/* Відправляємо цифру від 0 до 9 в один з чотирьох дусятків дисплея */
void WriteNumberToSegment(byte Segment, byte Value)
{
digitalWrite(LATCH_DIO,LOW);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
digitalWrite(LATCH_DIO,HIGH);
}
