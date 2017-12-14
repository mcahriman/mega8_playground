/*
 * pwm.h
 *
 *  Created on: Dec 12, 2017
 *      Author: manfred
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#define TIMER_2_PRESCALER_1024 (_BV(CS22) | _BV(CS21) | _BV(CS20))

// TODO: think about consistent API (if feasible and makes sense)

// 16 bit timer/Counter 1 fast pwm
void pwm_init();
void pwm_set_period(uint16_t);
void pwm_set_busy_cycle(uint16_t);
void timer2_init();

#endif /* TIMERS_H_ */
