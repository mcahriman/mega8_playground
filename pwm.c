#include <avr/io.h>
#include "pwm.h"

// this setup assumes you need only one pwm channel and
// variable pwm period really matters.
// if you need second 16 bit pwm channel, you'd
// probably found wrong piece of code

void pwm_init() {
	//PRR.PRTIM0 should be zero, nobody needs PRADC so turning it on
	//Select mode:
	// OC0B Enabled, non inverting. OC0A Disconnected
	// Selecting fast PWM mode 15

	//TODO: P1: RECHECK REGISTERS
	TCCR1A = _BV(COM1B1) | _BV(WGM10) | _BV(WGM11);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10); // no prescaler

	// Well, Now setting TOP Value (OCR1A)
	OCR1A = 255; // make TOP bit lower
	OCR1B = 0;  //
	DDRB |= _BV(DDB1); //set port as output
}

void pwm_set_period(uint16_t pwm_period) {
	OCR1A = pwm_period;
}

void pwm_set_busy_cycle(uint16_t busy_cycle) {
	OCR1B = busy_cycle;
}
