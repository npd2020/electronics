// Include the default XLR8HardwareSerial configuration
#include <XLR8Serial.h>

void setup() {

  // Turn on the XLR8 interrupts
  enableSerialInterrupts();

  // Start the builtin Serial interface
  Serial.begin(115200);

  // Start the XLR8 Serial interface
  XLR8Serial.begin(115200);

}

void loop() {

  // Print XLR8Serial data to the Serial interface
  while (XLR8Serial.available()) {
    Serial.write(XLR8Serial.read());
  }

  // Print Serial data to the XLR8Serial interface
  while (Serial.available()) {
    XLR8Serial.write(Serial.read());
  }

}
