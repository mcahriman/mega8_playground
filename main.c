/*
 * main.c
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
	init_uart();
	init_encoder_input();
	stdout = &uart_stdout;
}

//TODO: build proper transition map, events, states
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
			encoder_value += bit_is_set(PIND, PIND3) ? 1 : -1;
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
	printf("CN: %u, EV: %u CR: %c \n", count, encoder_value, cbuf);
}

//TODO: interrupts handling, factor out encoder reading for large chips

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

ISR(INT0_vect) {
	cli();
	io_state = ENCODER_UPDATE;
	sei();
}
