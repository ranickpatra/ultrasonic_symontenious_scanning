#include <Wire.h>


void setup() {

  Wire.begin(8);

  Wire.onRequest(revrt);


}



void loop() {


  delay(100);

}



void revrt() {
  Wire.write("hello\n");
}
