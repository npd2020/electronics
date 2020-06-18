
#define RED_PIN 8  // вихід для червоного кольору - PIN 8
#define YELLOW_PIN 10  // вихід для жовтого кольору - PIN 10
#define GREEN_PIN 12  // вихід для зеленого кольору - PIn 12

int red_on = 3000;  // час горіння червоного кольору
int red_yellow_on = 1000;  // час горіння червоного разом з жовтим
int green_on = 3000;  // час горіння зеленого
int green_blink = 500;  // час спалахування зеленого кольору, перед жовтим
int yellow_on = 3000;  // час горіння жовтого кольору

void setup() {
  pinMode(RED_PIN, OUTPUT);  
   pinMode(YELLOW_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RED_PIN, HIGH);   // запалюємо червоний кольор
  delay(red_on);                       // горить червоний впродовж 3с
  digitalWrite(YELLOW_PIN, HIGH);    // запалюємо жовтий
  delay(red_yellow_on);           // жовтий горить разом з червоним впродовж 1с   
  digitalWrite(RED_PIN, LOW);      // гасимо червоний
  digitalWrite(YELLOW_PIN, LOW);    // гасимо червоний
  digitalWrite(GREEN_PIN, HIGH);   // запалюємо зелений
  delay(green_on);                 // зелений горить впродовж 3с
  digitalWrite(GREEN_PIN, LOW);    // гасимо зелений
  for(int i=0;i<3;i=i+1){
    delay(green_blink);
    digitalWrite(GREEN_PIN, HIGH);
    delay(green_blink);
    digitalWrite(GREEN_PIN, LOW);
    }
     // зелений блимає 3 рази по 0,5 с і далі гасне
    digitalWrite(YELLOW_PIN, HIGH);  // запалюємо жовтий
    delay(yellow_on);                 // жовтий горить впродовж 1с
    digitalWrite(YELLOW_PIN, LOW);    // гасне жовтий
}
