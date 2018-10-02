
// trig 4, 5, 6, 7
// echo 8, 9, 10, 11

#include <Wire.h>


const unsigned long THRESHOLD = 24000;

int cm[4] = {0, 0, 0, 0};
unsigned long pulse_time[4] = {0, 0, 0, 0};
bool changed[4] = {false, false, false, false};
unsigned long now = 0;
unsigned long current_time;

void setup() {

	Wire.begin(0x05);						// begin I2C as slave on 0x05
	TWBR = 12;								// set SCL at 400KHz
 	DDRD |= B11110000;						// PD4, PD5, PD6, PD7 as output
	DDRB &= B11110000;						// PB0, PB1, PB2, PB3 as input
	DDRC |= B00000001;						// PC0 as output
	PORTD &= B00001111;   					// set PD4, PD5, PD6, PD7 low
	PORTC &= B11111110; 					// set PC0 low

	PCICR |= 1 << PCIE0;					// set PCIE0 to enable PCMSK0 scan
	PCMSK0 |= B00001111;					// to enable satate change interrupt

	Wire.onRequest(requestEvent);

}


void loop() {

	PORTC |= B00000001;   // set PC0 high to turn on power of Untrasonic sensor
	//delay(1);             // wait for 1 ms

	PORTD |= B11110000;
	delayMicroseconds(10);
	PORTD &= B00001111;
	now = micros();

	while((now + THRESHOLD + 4000) > micros());
	PORTC &= B11111110;   // set PC0 low to cut the power of Ultrasonic sensor
	for(int i=0; i < 4; i++) {
		if(changed[i]) {
			changed[i] = false;
			cm[i] = (int) ((pulse_time[i] / 2) * 0.032);			// calculate the distance in cm
		} else {
			cm[i] = 0;
		}
	}

}



// The interrupt service routine (ISR)
ISR(PCINT0_vect) {

	if(~PINB & B00001111 == B00001111)			// on interrupt if pin is not high
		return;

	current_time = micros() - now;					//  store the current_time in microseconds

	if(PINB & B00000001) {						// check is PB0 is high or not
		changed[0] = true;
		if(current_time < THRESHOLD) {
			pulse_time[0] = current_time;
		} else {
			pulse_time[0] = 0;
		}
	}

	if(PINB & B00000010) {						// check is PB1 is high or not
		changed[1] = true;
		if(current_time < THRESHOLD) {
			pulse_time[1] = current_time;
		} else {
			pulse_time[1] = 0;
		}
	}

	if(PINB & B00000100) {						// check is PB2 is high or not
		changed[2] = true;
		if(current_time < THRESHOLD) {
			pulse_time[2] = current_time;
		} else {
			pulse_time[2] = 0;
		}
	}

	if(PINB & B00001000) {						// check is PB3 is high or not
		changed[3] = true;
		if(current_time < THRESHOLD) {
			pulse_time[3] = current_time;
		} else {
			pulse_time[3] = 0;
		}
	}

}


// function that executes whenever data is requested by master
void requestEvent() {

	//4 * sizeof(int) = 4 * 2 = 8 bytes of data

	for(int i=0; i < 4; i++) {
		Wire.write(cm[i]);
	}

}
