#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 9;
int numberOfHorizontalDisplays = 1; 
int numberOfVerticalDisplays = 1; 

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

// 4 5 6
// 2 3
int** matrixMask = new int*[8];
short score = 0;

void setup() {
  randomSeed(analogRead(A0));
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP); 
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  matrix.setIntensity(0); 
  for(int i =0;i<8;i++){
    matrixMask[i] = new int[8];
    for(int j = 0;j<8;j++)
      matrixMask[i][j]=0;
  }
  matrix.fillScreen(LOW);
  matrix.write();
  Serial.begin(9600);
}

void printdigit(int d)
{
  matrix.setRotation( 0, 1 );
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


struct Figure {
  int nx;
  int ny;
  int** mask;

  ~Figure(){
    for(int i = 0;i<ny;i++)
      delete [] mask[i];
    delete[] mask;
  }
  Figure(int nx, int ny, int** mask): nx(nx),ny(ny),mask(mask){}
  Figure(int type){
    mask = new int*[2];
    for(int i =0;i<2;i++){
      mask[i] = new int[3];
      for(int j =0;j<3;j++)
        mask[i][j]=0;
    }
    if(type == 1){
      nx = 1;
      ny =1;
      mask[0][0] = 1;
    }
    if(type == 2){
      nx = 3;
      ny =2;
      mask[0][0] = 1;
      mask[0][1] = 1;
      mask[1][1] = 1;
      mask[1][2] = 1;
    }
    if(type == 3){
      nx = 3;
      ny =2;
      mask[1][0] = 1;
      mask[0][1] = 1;
      mask[1][1] = 1;
      mask[0][2] = 1;
    }
    if(type == 4){
      nx = 3;
      ny =2;
      mask[0][1] = 1;
      mask[1][0] = 1;
      mask[1][1] = 1;
      mask[1][2] = 1;
    }
    if(type == 5){
      nx = 3;
      ny =2;
      mask[0][0] = 1;
      mask[1][0] = 1;
      mask[1][1] = 1;
      mask[1][2] = 1;
    }
    if(type == 6){
      nx = 3;
      ny =2;
      mask[0][0] = 1;
      mask[1][0] = 1;
      mask[0][1] = 1;
      mask[0][2] = 1;
    }
    if(type == 7){
      nx = 3;
      ny =1;
      mask[0][0] = 1;
      mask[0][1] = 1;
      mask[0][2] = 1;
    }
    if(type == 8){
      nx = 2;
      ny =2;
      mask[0][0] = 1;
      mask[0][1] = 1;
      mask[1][0] = 1;
    }
    if(type == 9){
      nx = 2;
      ny =2;
      mask[0][0] = 1;
      mask[0][1] = 1;
      mask[1][0] = 1;
      mask[1][1] = 1;
    }
  }
};

bool hasActiveFig = false;
Figure* activef;
int x=0;
int y=0;

bool isSomethingUnder(){
  if(y == activef->ny-1) {Serial.println("GROUND");return true;}
  for(int j =0;j<activef->nx;j++){
    for(int i = activef->ny-1;i>=0;i--){
      if(activef->mask[i][j]){
        if(matrixMask[y-i-1][x+j])
          return true;
        break;
      }
    }
  }
  return false;
}

bool isSomethingRight(){
  if(x == 8-activef->nx) {Serial.println("Right border");return true;}
  for(int j =0;j<activef->ny;j++){
    for(int i = activef->nx-1;i>=0;i--){
      if(activef->mask[j][i]){
        if(matrixMask[y-j][x+i+1])
          return true;
        break;
      }
    }
  }
  return false;
}

bool isSomethingLeft(){
  if(x == 0) {Serial.println("Left border");return true;}
  for(int j =0;j<activef->ny;j++){
    for(int i = 0;i<activef->nx;i++){
      if(activef->mask[j][i]){
        if(matrixMask[y-j][x+i-1])
          return true;
        break;
      }
    }
  }
  return false;
}

void removeLine(int line){
  for(int j = line;j<6;j++)
    for(int i =0;i<8;i++)
      matrixMask[j][i] = matrixMask[j+1][i]; 
}

void checkIsFullLineExist(){
  bool isfull;
  for(int j =0;j<6;j++){
    isfull = true;
    for(int i =0;i<8;i++){
      if(!matrixMask[j][i]){
        isfull = false;
        break;
      }
    }
    if(isfull)
      removeLine(j);
  }
}

void endGame(){
  matrix.fillScreen(LOW);
  printdigit(score);
  matrix.write(); 
  while(true){}
}

void moveActive(){
  bool check = isSomethingUnder();
  Serial.println(check);
  if(check){
    if(y >= 6) endGame();
    for(int i = y;i>-activef->ny+y;i--)
      for(int j =x;j<activef->nx+x;j++)
        matrixMask[i][j] = (activef->mask[y-i][j-x] || matrixMask[i][j]);
    hasActiveFig=false;
    checkIsFullLineExist();
    return;
  }
  y--;
}

void falldown(){
  while(hasActiveFig)
    moveActive();
}

void graph(){
  matrix.fillScreen(LOW);
  for(int i = 0;i<8;i++)
    for(int j = 0;j<8;j++)
      matrix.drawPixel(i, j, matrixMask[j][i]);
  for(int i = 0;i<activef->nx;i++)
    for(int j = 0;j<activef->ny;j++)
      if(activef->mask[j][i])
        matrix.drawPixel(x+i,y-j, activef->mask[j][i]);
  matrix.write();
}

void rotateRight(){
  int xsize = activef->nx;
  int ysize = activef->ny;
  Figure* rotatedF = new Figure(ysize,xsize,0);
  rotatedF->mask = new int*[xsize];
  for(int i = 0;i<xsize;i++){
    rotatedF->mask[i] = new int[ysize];
    for(int j =0;j<ysize;j++)
      rotatedF->mask[i][j]=0;
  } 
  for(int i = 0;i<xsize;i++)
    for(int j = 0;j<ysize;j++)
      rotatedF->mask[i][j]=activef->mask[ysize-j-1][i];

  activef = rotatedF;
}

void wait(){
  for(int t = 0;t<4;t++){
    bool turnRight = !digitalRead(4);
    bool turnDown = !digitalRead(3);
    bool turnLeft =! digitalRead(2);
    bool rotRight =! digitalRead(5);
    bool rotLeft = !digitalRead(6);
    if(turnRight && !turnLeft)
      if(!isSomethingRight()){
        x++;
        graph();
      }
    if(!turnRight && turnLeft)
      if(!isSomethingLeft()){
        x--;
        graph();
      }
    if(turnDown){
      falldown();
      graph();
    }
    if(rotRight && !rotLeft){
      rotateRight();
      graph();
    }
    delay(150);
  }
}

void loop() {
  if(!hasActiveFig){
    score ++;
    Serial.print("creating new figure with type: ");
    hasActiveFig=true;
    int type = random(1,10);
    Serial.print(type);
    Serial.print("   ");
    activef = new Figure(type);
    x = 4;
    y = 7;
    Serial.println(type);
    graph();
    wait();
  }
  
  moveActive();
  Serial.print("moved  ");
  Serial.print(x);
  Serial.print("  ");
  Serial.println(y);

  graph();
  wait();
}
