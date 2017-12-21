#include <avr/io.h>
//for single encoder at the moment

void encoder_init() {
	DDRD &= ~(_BV(DDD2) | _BV(DDD7)); //clear bits on inputs
	PORTD |= _BV(PD2) | _BV(PD7); // Enable pull-up resistor
	MCUCR |= _BV(ISC01); // ISC00 0, ISC01 1: Generate interrupt on falling edge
	GICR |= _BV(INT0); // Enable interrupt INT0
}
