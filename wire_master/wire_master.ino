#include <Wire.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                   // start Serial communation at 115200
  Wire.begin();                           // Start Wire as master
  TWBR = 12;                              // set I2C clock speed 400KHz

}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.requestFrom(8, 6);

  while (Wire.available()) {
    Serial.print((char) Wire.read());
  }

  Serial.println();

  delay(500);

}
