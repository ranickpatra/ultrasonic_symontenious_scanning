
// trig 4, 5, 6, 7
// echo 8, 9, 10, 11

#include <Wire.h>



uint16_t cm[4] = {0, 0, 0, 0};

void setup() {


	Wire.begin(0x05);						// begin I2C as slave on 0x05
	//TWBR = 12;								// set SCL at 400KHz
 	DDRD |= B11110000;						// PD4, PD5, PD6, PD7 as output
	DDRB &= B11110000;						// PB0, PB1, PB2, PB3 as input
	DDRC |= B00000001;						// PC0 as output
	PORTD &= B00001111;   					// set PD4, PD5, PD6, PD7 low
	PORTC &= B11111110; 					// set PC0 low

	//PCICR |= 1 << PCIE0;					// set PCIE0 to enable PCMSK0 scan
	//PCMSK0 |= B00001111;					// to enable satate change interrupt

	Wire.onRequest(requestEvent);
}


void loop() {

	//PORTC |= B00000001;   // set PC0 high to turn on power of Untrasonic sensor
	//delay(1);             // wait for 1 ms



	//PORTC &= B11111110;   // set PC0 low to cut the power of Ultrasonic sensor
	for(int i=0; i < 4; i++) {
		PORTD |= 1 << (4+i);
		delayMicroseconds(10);
		PORTD &= B00001111;
		cm[i] = to_cm(pulseIn(i + (1 << 3), HIGH, 20000) / 2);
	}

	delay(50);


}


uint16_t to_cm(unsigned long m_time) {
	return (uint16_t) (m_time * 0.0335);
}


// function that executes whenever data is requested by master
void requestEvent() {
	//4 * sizeof(int) = 4 * 2 = 8 bytes of data

	for(int i=0; i < 4; i++) {
		Wire.write((cm[i] >> 8) & 0xFF);
		Wire.write(cm[i] & 0xFF);
	}

}
