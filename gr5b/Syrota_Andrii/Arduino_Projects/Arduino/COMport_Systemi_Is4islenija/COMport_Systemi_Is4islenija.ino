int symbol = 33;

void setup() {
  Serial.begin(9600);
  Serial.println("ASCII Table ~ Character Map");
}

void loop() {
  Serial.write(symbol);
  Serial.print(", dec: ");
  Serial.print(symbol);
  Serial.print(", hex: ");
  Serial.print(symbol, HEX);
  Serial.print(", oct: ");
  Serial.print(symbol, OCT);
  Serial.print(", bin: ");
  Serial.println(symbol, BIN);
  if(symbol == 126) {
    while(true) {
      continue;
    }
  }
  symbol++;  
}
