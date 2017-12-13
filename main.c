/*
 * main.c
 *
 *	PWM control routine for TDA5140 BLDC motor
 *	Target hardware: atmega8
 *
 *	License: meh
 *
 *  Created on: Dec 5, 2017
 *      Author: manfred
 */

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "main.h"
#include "uart.h"
#include "encoder.h"
#include "pwm.h"

#define PWM_Period 127

enum io_state_t {
	IDLE, AWAITING_ANY_RESPONSE, AWAITING_UART_ECHO, ENCODER_UPDATE
} io_state;

char cbuf;


int main() {
	sei();
	init();
	loop();
}

void init() {
	uart_init();
	encoder_init();
	pwm_init();
	pwm_set_busy_cycle(0);
	stdout = &uart_stdout;
}

//TODO: design FSMs (tacho data handling)
void loop() {

	uint16_t loop_counter = 0;
	uint8_t encoder_value = 0;
	for (;;) {
		switch (io_state) {
		case AWAITING_ANY_RESPONSE:
			display_vals(loop_counter, encoder_value);
			io_state = IDLE;
			break;
		case AWAITING_UART_ECHO:
			printf("some data received, %c\n", cbuf);
			io_state = IDLE;
			break;
		case ENCODER_UPDATE:
			encoder_value += bit_is_set(PIND, PIND3) ? // excuse me
					((encoder_value <= PWM_Period) ? 1 : 0) : // sorry
							((encoder_value > 0) ? -1 : 0); // (sorry)
			// ...
			encoder_value =
					encoder_value > PWM_Period ? PWM_Period : encoder_value;

			pwm_set_busy_cycle(encoder_value);


			io_state = IDLE;
			break;
		case IDLE:
			// TODO: Anything that can not be handled in interrupt should polled
			break;
		default:
			break;
		}

		loop_counter++;
	}
}

void display_vals(uint16_t count, uint8_t encoder_value) {
	//CN: cycle number (bit useless, yup)
	//EV: encoder value (debug value)
	//CR: char received
	printf("CN: %u, EV: %u CR: %c \n", count, encoder_value, cbuf);
}

//TODO: get a clue on better and moar stylish interrupt routines

ISR(USART_RXC_vect) {

	cli();
	cbuf = UDR; //UDR Should be read explicitly
	switch (cbuf) {
	case 'a':
		io_state = AWAITING_ANY_RESPONSE;
		break;
	case 'b':
	default:
		io_state = AWAITING_UART_ECHO;
		break;
	}
	sei();
}

//TODO: meh, I need serve this interrupt inside encoder library,
//		still in search for elegant approach, as in prev. routine
ISR(INT0_vect) {
	cli();
	io_state = ENCODER_UPDATE;
	sei();
}

//TODO: write small utility for using binary protocol

/**
 * Final protocol is somewhat like:
 * 			octet content		description
 * 			0x00 MAGIC_NUMBER	(TR START INDICATOR)
 * 			0x01 COMMAND		(0x00 tacho output 0x01 - set RPM)
 * 			0x02 ARGUMENT		(if COMMAND is 0x01 - RPM)
 *
 */

//TODO: calculate RPM somehow (e.g prescaler on 8-bit OCR channel)

//TODO: eradicate todos,
//NOTE: this is still hobby project and I'm wearing protective
//      googles while using this piece of code. spin safe.

//TODO: integrate watchdog
