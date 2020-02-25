boolean butt_flag = 0; 
boolean butt;
boolean led_flag = 0;
unsigned long last_press;
byte led_counter = 4;

void setup() {
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(7,0);
  digitalWrite(8,0);  
}

void loop() {
  butt = !digitalRead(3);
  
  if (butt == 1 && butt_flag == 0 && millis() - last_press > 300)
  {
    butt_flag = 1;
    led_flag = 1;
    Serial.println("Button pressed");
    if (led_counter > 8)
    {
      led_counter = 4;
      led_flag =0;
      for(int i=4; i<=8; i++)
      {
        digitalWrite(i,led_flag);
      }
    }
    else
    {
      Serial.println(led_counter);
      digitalWrite(led_counter, led_flag);
      led_counter++;
    }
    last_press = millis();
  }
  if ( butt == 0 && butt_flag == 1)
  {
    butt_flag = 0;
    Serial.println("Button released");
    
  }
}
