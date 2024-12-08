/*
 * beep.h
 *
 *  Created on: 08 Apr,2024
 *      Author: Tinashe
 */

#ifndef BEEP_H_
#define BEEP_H_

void delay_ms(uint32_t delay);
void PIT_Init(void);
//void PIT_StartTimer(uint32_t delay_ms);
void LED_Configuration(void);
void stoptimmer(void);
void beepfrequency(int freq);

#endif /* BEEP_H_ */
