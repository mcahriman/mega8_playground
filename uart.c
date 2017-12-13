/*
 * uart.c
 *
 *  Created on: Dec 12, 2017
 *      Author: manfred
 */
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"


FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int uart_putchar(char c, FILE *stream) {
	if (c == '\n')
		uart_putchar('\r', stream);
	loop_until_bit_is_set(UCSRA, UDRE); //busy wait until transmit buf is empty
	UDR = c;
	return 0;
}

void uart_init() {
	UCSRB |= (1 << RXEN) | (1 << TXEN) | _BV(RXCIE); // TX, RX and RX interrupt
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); //
	UBRRL = 0x19; //At 16 MHz 38400 is reasonable choice for a bit rate
}
