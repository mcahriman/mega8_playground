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


static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
		_FDEV_SETUP_WRITE);

enum prog_state_t {
	IDLE, AWAITING_ANY_RESPONSE, AWAITING_UART_ECHO, ENCODER_UPDATE
} prog_state;

char cbuf;

static int uart_putchar(char c, FILE *stream) {
	if (c == '\n')
		uart_putchar('\r', stream);
	loop_until_bit_is_set(UCSRA, UDRE); //busy wait until transmit buf is empty
	UDR = c;
	return 0;
}

void init_uart() {
	UCSRB |= (1 << RXEN) | (1 << TXEN) | _BV(RXCIE); // TX, RX and RX interrupt
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); //
	UBRRL = 0x19; //At 16 Mhz 38400 is reasonable bit rate
}

void init_encoder_input() {
	DDRD &= ~( _BV(DDD2) | _BV(DDD3)); //clear bits on inputs
	PORTD |= _BV(PD2) | _BV(PD3); // Enable pull-up resistor
	MCUCR |= _BV(ISC01); // ISC00 0, ISC01 1: Generate interrupt on falling edge
	GICR |= _BV(INT0); // Enable interrupt INT0
}

int main() {
	sei();
	init();
	loop();
}

void init() {
	init_uart();
	init_encoder_input();
	stdout = &mystdout;

}

void loop() {
	uint16_t loop_counter = 0;
	uint8_t encoder_value = 0;
	for (;;) {
		switch (prog_state) {
		case AWAITING_ANY_RESPONSE:
			display_vals(loop_counter, encoder_value);
			prog_state = IDLE;
			break;
		case AWAITING_UART_ECHO:
			printf("some data received, %c\n", cbuf);
			prog_state = IDLE;
			break;
		case ENCODER_UPDATE:
			encoder_value += bit_is_set(PIND, PIND3) ? 1 : -1;
			prog_state = IDLE;
			break;
		case IDLE:
			// TODO: Anything that can not be handled in interrupt should polled
			// And next state toggled
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

ISR(USART_RXC_vect) {

	cli();
	cbuf = UDR; //UDR Should be read explicitly
	switch (cbuf) {
	case 'a':
		prog_state = AWAITING_ANY_RESPONSE;
		break;
	case 'b':
	default:
		prog_state = AWAITING_UART_ECHO;
		break;
	}
	sei();
}

ISR(INT0_vect) {
	cli();
	prog_state = ENCODER_UPDATE;
	sei();
}
