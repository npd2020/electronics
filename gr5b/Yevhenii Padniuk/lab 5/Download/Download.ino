// Визначаємо контакти зсувового регістру, застосовувані для семисегментного індикатора
#define LATCH_DIO 4 //лінія синхронізації даних, засувка (LCHCLK)
#define CLK_DIO 7 //лінія тактування (SFTCLK)
#define DATA_DIO 8 //лінія пеоедачі даних (SDI)

/* байти чисел від 0 до 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
/* Байт-карти для выбору десятку дисплея від 1 до 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};
 
void setup (){
 
/* Встановлення портів DIO як виходи */
pinMode(LATCH_DIO,OUTPUT);
pinMode(CLK_DIO,OUTPUT);
pinMode(DATA_DIO,OUTPUT);
}
 
void loop(){
 
/* Обновити дисплей з новими значеннями лічильника */
WriteNumberToSegment(0 , 5);//записати в нульовий десяток 5
WriteNumberToSegment(1 , 6);//записати в перший десяток 6
WriteNumberToSegment(2 , 7);//записати в другий десяток 7
WriteNumberToSegment(3 , 8);//записати в третій десяток 8
}
 
/* Відправляємо цифру від 0 до 9 в один з чотирьох дусятків дисплея */
void WriteNumberToSegment(byte Segment, byte Value)
{
digitalWrite(LATCH_DIO,LOW);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
digitalWrite(LATCH_DIO,HIGH);
}
