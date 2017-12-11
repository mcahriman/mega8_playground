#include <avr/io.h>
//for single encoder at the moment

void init_encoder_input() {
	DDRD &= ~(_BV(DDD2) | _BV(DDD3)); //clear bits on inputs
	PORTD |= _BV(PD2) | _BV(PD3); // Enable pull-up resistor
	MCUCR |= _BV(ISC01); // ISC00 0, ISC01 1: Generate interrupt on falling edge
	GICR |= _BV(INT0); // Enable interrupt INT0
}
