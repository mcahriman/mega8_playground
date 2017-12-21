/*
 * pwm.h
 *
 *  Created on: Dec 12, 2017
 *      Author: manfred
 */

#ifndef TIMERS_H_
#define TIMERS_H_

// clkio/1024
#define TIMER_2_PRESCALER_1024 (_BV(CS22) | _BV(CS21) | _BV(CS20))

// here we define, how much overflows we will get
// using 1024 times prescaled timer during one second
// to avoid computations

#if F_CPU==16000000
#define SECOND_OVF_INTERRUPT_COUNT 61
#elif F_CPU==8000000
#define SECOND_OVF_INTERRUPT_COUNT 30
#else
#error "Current F_CPU is not supported. Add your values please"
#endif

// TODO: think about consistent API (if feasible and makes sense)

// 16 bit timer/Counter 1 fast pwm
void pwm_init();
void pwm_set_period(uint16_t period);
void pwm_set_busy_cycle(uint16_t busy_cycle);
void timer2_init();

#endif /* TIMERS_H_ */
