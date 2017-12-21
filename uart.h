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

//this is somewhat strange attempt to get consistant stuff at list
//somewhere, but now uart in this project is compatible both for 16MHz and 8

#if F_CPU==16000000
#define UBRRL_38400_VAL 0x19
#elif F_CPU==8000000
#define UBRRL_38400_VAL 0x00C
#else
#error "Current F_CPU is not defined by current uart impl. Refer to uart.h"
#endif

#endif /* UART_H_ */
