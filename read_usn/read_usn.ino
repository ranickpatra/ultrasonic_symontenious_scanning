
// trig 4, 5, 6, 7
// echo 8, 9, 10, 11

unsigned long pulse_time[4] = {0, 0, 0, 0};

void setup() {

  DDRD |= B11110000;    // PD4, PD5, PD6, PD7 as output
  DDRB &= B11110000     // PB0, PB1, PB2, PB3 as input
  DDRC |= B00000001;    // PC0 as output
  PORTD &= B00001111;   // set PD4, PD5, PD6, PD7 low
  PORTC &= B11111110;   // set PC0 low

}


void loop() {

  PORTC |= B00000001;   // set PC0 high to turn on power of Untrasonic sensor
  //delay(1);             // wait for 1 ms



  PORTC &= B11111110;   // set PC0 low to cut the power of Ultrasonic sensor

}
