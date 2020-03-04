void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  int Antibrightness = analogRead(A0);
  Serial.println(Antibrightness);
  if (Antibrightness < 10000 && Antibrightness >= 700) 
  { //1
    digitalWrite(13, 0);
    digitalWrite(12, 1);
    digitalWrite(11, 0);
    digitalWrite(10, 0);
    digitalWrite(9, 1);
    digitalWrite(8, 1);
    digitalWrite(7, 0);
    digitalWrite(6, 0); 
  }
  else if(Antibrightness < 700 && Antibrightness >= 635)
  { //2
    digitalWrite(13, 1);
    digitalWrite(12, 1);
    digitalWrite(11, 0);
    digitalWrite(10, 1);
    digitalWrite(9, 1);
    digitalWrite(8, 0);
    digitalWrite(7, 1);
    digitalWrite(6, 1);
  }
  else if(Antibrightness < 635 && Antibrightness >= 570)
  { //3
    digitalWrite(13,1);
    digitalWrite(12,1);
    digitalWrite(11,0);
    digitalWrite(10,1);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,1);
    digitalWrite(6,0);
  }
  else if(Antibrightness < 570 && Antibrightness >= 505)
  { //4
    digitalWrite(13,0);
    digitalWrite(12,1);
    digitalWrite(11,1);
    digitalWrite(10,1);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,0);
    digitalWrite(6,0);
  }
  else if(Antibrightness < 505 && Antibrightness >= 440)
  { //5
    digitalWrite(13,1);
    digitalWrite(12,0);
    digitalWrite(11,1);
    digitalWrite(10,1);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,1);
    digitalWrite(6,0);
  }
  else if(Antibrightness < 440 && Antibrightness >= 375)
  { //6
    digitalWrite(13,1);
    digitalWrite(12,0);
    digitalWrite(11,1);
    digitalWrite(10,1);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,1);
    digitalWrite(6,1);
  }
  else if(Antibrightness < 375 && Antibrightness >= 310)
  { //7
    digitalWrite(13,1);
    digitalWrite(12,1);
    digitalWrite(11,0);
    digitalWrite(10,0);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,0);
    digitalWrite(6,0);
  }
  else if(Antibrightness < 310 && Antibrightness >= 245)
  { //8
    digitalWrite(13,1);
    digitalWrite(12,1);
    digitalWrite(11,1);
    digitalWrite(10,1);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,1);
    digitalWrite(6,1);
  }
  else
  { //9
    digitalWrite(13,1);
    digitalWrite(12,1);
    digitalWrite(11,1);
    digitalWrite(10,1);
    digitalWrite(9,1);
    digitalWrite(8,1);
    digitalWrite(7,1);
    digitalWrite(6,0);
  }
}
