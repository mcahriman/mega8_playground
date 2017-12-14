#include "timers.h"

#include <avr/io.h>

/**
 *  this setup assumes you need only one pwm channel and
 *  variable PWM period really matters.
 *  if you need second 16 bit PWM channel, you'd
 *  probably found wrong piece of code
 *
 */

void pwm_init() {
	//PRR.PRTIM0 should be zero, nobody needs PRADC so turning it on
	//Select mode:
	// OC0B Enabled, non inverting. OC0A Disconnected
	// Selecting fast PWM mode 15

	TCCR1A = _BV(COM1B1) | _BV(WGM10) | _BV(WGM11);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10); // no prescaler

	// Well, Now setting TOP Value (OCR1A)
	OCR1A = 255;
	OCR1B = 0;
	DDRB |= _BV(DDB2); //set port as output
}

void pwm_set_period(uint16_t pwm_period) {
	OCR1A = pwm_period;
}

void pwm_set_busy_cycle(uint16_t busy_cycle) {
	OCR1B = busy_cycle;
}

/**
 * Initializes timer/counter2 in normal mode,
 * enabling overflow interrupt
 */
void timer2_init() {
	TCCR2 |= TIMER_2_PRESCALER_1024; // clkio/1024, (1/61 sec rougly for full cycle)
	TIMSK |= TOIE2; //enable interrupt
}
