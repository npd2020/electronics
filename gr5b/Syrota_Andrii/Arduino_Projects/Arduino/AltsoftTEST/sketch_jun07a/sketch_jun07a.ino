

void setup()
{
  // Open serial communications and wait for port to open:
 Serial.begin(9600);
 
  }



void loop() // run over and over
{
  if (Serial.available()>0){

  Serial.println(Serial.read());
 }

}
