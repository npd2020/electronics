
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

void setup() {

  pinMode(1, OUTPUT);//1
  pinMode(2, OUTPUT);//2
  pinMode(3, OUTPUT);//
  pinMode(4, OUTPUT);//
  pinMode(5, OUTPUT);//
  pinMode(6, OUTPUT);//
  pinMode(7, OUTPUT);//
  pinMode(8, OUTPUT);//
}

void loop() {
  for (int i = 1; i < 9; ++i) {
    digitalWrite(i,HIGH);
  }
}
