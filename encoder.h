/*
 * encoder.h
 *
 *  Created on: Dec 12, 2017
 *      Author: manfred
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#if defined  (__AVR_ATmega8__)
#else
#error("Device not supported, only ATmega8 at the moment")
#endif


void encoder_init();

#endif /* ENCODER_H_ */
