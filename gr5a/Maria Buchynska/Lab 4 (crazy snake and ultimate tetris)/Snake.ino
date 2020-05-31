#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 9;
int numberOfHorizontalDisplays = 1; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
struct coord{
  int x;
  int y;
};
coord eat={random(8), random(8)};
int len=1;
coord*snake= new coord [64];
void setup() {
  randomSeed(analogRead(0));
    matrix.setIntensity(4); // яркость от 0 до 15
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    pinMode(5,INPUT);
    PORTD = 0b00111100;
    Serial.begin(9600);
    
snake[0]={3,0};
snake[1]={2,0};
snake[2]={1,0};
snake[3]={0,0};
}
int  x=0, y=0;
int dirX=1, dirY=0;


void printdigit(int d)
{
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<8; j++)
      matrix.drawPixel(i,j, LOW);
    matrix.write(); 
  }
  int a=d/10; 
  for(int k=0; k<2; k++)
  {
  switch(a)
  {
    case 0:
    for(int i=1; i<6; i++)
    {
    matrix.drawPixel(i,4*k, HIGH);
    matrix.drawPixel(i,2+4*k, HIGH);    
    }
    matrix.drawPixel(1,1+4*k, HIGH);    
    matrix.drawPixel(5,1+4*k, HIGH); 
    break;
    
    case 1:
    for(int i=1; i<6; i++)       
    matrix.drawPixel(i,2+4*k, HIGH);      
    break;
    
    case 2:
    for(int i=1; i<6; i++)
    {
      if(i!=4)
      { matrix.drawPixel(i,4*k, HIGH);
        if(i!=2) matrix.drawPixel(i,1+4*k, HIGH);
      }
    if(i!=2)
    matrix.drawPixel(i,2+4*k, HIGH);    
    }    
    break;
    
    case 3:
    for(int i=1; i<6; i++) 
    {
    matrix.drawPixel(i,2+4*k, HIGH); 
    if(i%2==1)
    {matrix.drawPixel(i,4*k, HIGH);
    matrix.drawPixel(i,1+4*k, HIGH);} 
    }      
    break;
    
    case 4:
    for(int i=1; i<6; i++)
    { 
    matrix.drawPixel(i,2+4*k, HIGH); 
    if(i>2) matrix.drawPixel(i,4*k, HIGH); 
    }   
    matrix.drawPixel(3,1+4*k, HIGH);
    break;
    
    case 5:
    
    for(int i=1; i<6; i++)
    {
      if(i!=2)
      { matrix.drawPixel(i,4*k, HIGH);
        if(i!=4) matrix.drawPixel(i,1+4*k, HIGH);
      }
    if(i!=4)
    matrix.drawPixel(i,2+4*k, HIGH);    
    }   
    break;
    
    case 6:
    for(int i=1; i<6; i++)
    {
    matrix.drawPixel(i,4*k, HIGH);
    matrix.drawPixel(i,2+4*k, HIGH);  
    if(i%2==1) matrix.drawPixel(i,1+4*k, HIGH);  
    }
    matrix.drawPixel(4,2+4*k, LOW);    
    break;
    
    case 7:
    for(int i=1; i<6; i++)
    {    
    matrix.drawPixel(i,2+4*k, HIGH);    
    }
    matrix.drawPixel(5,4*k, HIGH);
    matrix.drawPixel(5,1+4*k, HIGH);     
    break;
    
    case 8:
    for(int i=1; i<6; i++)
    {
    matrix.drawPixel(i,4*k, HIGH);
    matrix.drawPixel(i,2+4*k, HIGH); 
    if(i%2==1) matrix.drawPixel(i,1+4*k, HIGH);   
    }     
    break;
    
    case 9:
    for(int i=1; i<6; i++)
    {
    matrix.drawPixel(i,4*k, HIGH);
    matrix.drawPixel(i,2+4*k, HIGH);
    if(i%2==1) matrix.drawPixel(i,1+4*k, HIGH);     
    }
    matrix.drawPixel(2,4*k, LOW);     
    break;
  }
  a=d%10;
  }
  matrix.write(); 
}


void loop() {

  
snake[0].x=(snake[0].x+8)%8;
 snake[0].y=(snake[0].y+8)%8;
for(int i=0; i<len; i++)
    {
      matrix.drawPixel((snake[i].x+8)%8, (snake[i].y+8)%8, LOW);
    }   
    matrix.write();  
    
for(int j=len-1;j>0; j--)
{
  snake[j].x=(snake[j].x+8)%8;
  snake[j].y=(snake[j].y+8)%8; 
  if(snake[j].x != snake[j-1].x || snake[j].y != snake[j-1].y)
  {  
   snake[j].x=snake[j-1].x;
   snake[j].y=snake[j-1].y;  
  } 
 }


snake[0].x+=dirX;
snake[0].y+=dirY;
 
snake[0].x = (snake[0].x + 8) % 8;
snake[0].y = (snake[0].y + 8) % 8;  
 
 for(int i=0; i<len; i++)
 {
      matrix.drawPixel((snake[i].x+8)%8, (snake[i].y+8)%8, HIGH);
 }   
  matrix.drawPixel(eat.x, eat.y, HIGH);
    matrix.write(); 
     for(int k=0; k<len; k++)
      {
        for( int j=k+1; j<len; j++)
        {
          if(snake[k].x==snake[j].x&&snake[k].y==snake[j].y)
          {
            printdigit(len);
            while(1==1)
            {
              
            }
          }
        }
      }
   
    if(eat.x==snake[0].x&&eat.y==snake[0].y)
    {
      snake[len].x=snake[len-1].x;
      snake[len].y=snake[len-1].y;
      len++;
       matrix.drawPixel(eat.x, eat.y, LOW);
      eat={random(8), random(8)};
       matrix.drawPixel(eat.x, eat.y, HIGH);
      matrix.write();
      }
    for(int k=0;k<500;k++)
    {
      if(k%100==0)
      {
       matrix.drawPixel(snake[0].x, snake[0].y, LOW);
       matrix.drawPixel(eat.x, eat.y, LOW);
       matrix.write();
      }
      if(k%100==50)
      {
       matrix.drawPixel(snake[0].x, snake[0].y, HIGH);
       matrix.drawPixel(eat.x, eat.y, HIGH);
       matrix.write();
      }
      
      
if(digitalRead(2)==LOW&&dirX!=-1)
{  dirX=1;
  dirY=0;}
  if(digitalRead(3)==LOW&&dirY!=-1)
{  dirX=0;
  dirY=1;}
  if(digitalRead(4)==LOW&&dirX!=1)
{  dirX=-1;
  dirY=0;}
  if(digitalRead(5)==LOW&&dirY!=1)
{  dirX=0;
  dirY=-1;}
  delay(1);
  }
  

   
    
}
