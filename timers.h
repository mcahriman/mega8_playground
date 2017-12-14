/*
 * pwm.h
 *
 *  Created on: Dec 12, 2017
 *      Author: manfred
 */

#ifndef PWM_H_
#define PWM_H_

// TODO: think about consistent API (if feasible and makes sense)


// 16 bit timer/Counter 1 fast pwm
void pwm_init();
void pwm_set_period(uint16_t);
void pwm_set_busy_cycle(uint16_t);

#endif /* PWM_H_ */
