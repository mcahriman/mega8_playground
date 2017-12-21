/*
 * main.h
 *
 *  Created on: Dec 5, 2017
 *      Author: manfred
 */

#ifndef MAIN_H_
#define MAIN_H_

#define ENCODER_INT_PIN PD2
#define ENCODER_DATA_PINS PIND
#define ENCODER_DATA_PORT PORTD
#define ENCODER_DATA_PIN PIND7


#define ENCODER_INTERRUPT_VECT INT0_vect
#define TACHO_INTERRUPT INT1

void init();
void loop();
void display_vals(uint16_t, uint8_t);

#endif /* MAIN_H_ */
