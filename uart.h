/*
 * uart.h
 *
 *  Created on: Dec 12, 2017
 *      Author: manfred
 */

#ifndef UART_H_
#define UART_H_

FILE uart_stdout;
void uart_init();
int uart_putchar(char c, FILE *stream);

#endif /* UART_H_ */
