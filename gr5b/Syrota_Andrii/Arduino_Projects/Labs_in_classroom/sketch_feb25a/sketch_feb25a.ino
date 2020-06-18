//Моя версия генератора сигналлов, разработанна для рабочих целей.
//Страница проэкта  http://srukami.inf.ua/signalgenerator.html
#include <PWM.h>

#define led  9   //пин для генератора сигналов (не менять)
//#################№№№№№№####пользовательские настройки
   
int PWM = 100;//стартовое значение ШИМ от 0 до 255        
int32_t frequency = 6000; //стартовое значение частоты в Гц
byte cont=40;//контрастность дисплея
//###########################################################
byte hag=0;
int mnog=0;
boolean flag=0;
byte mass[85];
byte x=0;     
void setup(){
InitTimersSafe(); 
ADCSRA = 0b11100010;
ADMUX = 0b01100100;
bool success = SetPinFrequencySafe(led, frequency);
delay(50);
      }
      
void Zamer(){
  for(byte i=0;i<84;i++){ 
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10;
  mass[i]=ADCH;
  }
}
void Zamer1(){
  for(byte i=0;i<84;i++){ 
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10;
  mass[i]=ADCH;
  delayMicroseconds(5);
  }
}
void Zamer2(){
  for(byte i=0;i<84;i++){ 
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10;
  mass[i]=ADCH;
  delayMicroseconds(50);
  }
}

void loop() {
if(frequency>5000){Zamer();}
if(frequency<=5000){Zamer1();}
if(frequency<=1000){Zamer2();}
 
          
if (flag==0){//флаг выборов режима настройки ШИМ или Частоты
            if(digitalRead(levo)==HIGH){
              frequency=frequency-mnog;
              if(frequency<0){frequency=0;}
              bool success = SetPinFrequencySafe(led, frequency);
              delay(3);//защита от дребезга 
            }
            if(digitalRead(pravo)==HIGH){
              frequency=frequency+mnog;
              bool success = SetPinFrequencySafe(led, frequency);
              delay(3);//защита от дребезга 
            }  
}
            
}         
   
    
pwmWrite(led, PWM);
delay(300);  
}
