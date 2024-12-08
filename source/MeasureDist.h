/*
 * MeasureDist.h
 *
 *  Created on: 02 Apr,2024
 *      Author: Tinashe
 */

#ifndef MEASUREDIST_H_
#define MEASUREDIST_H_


void delay_ms1(int n);		//software delay
void initializeRadar();
void init_timerRadar();
void init_PWM_Capture_Pins();
void distance(void);


uint32_t read_distance(uint32_t echoInterval, uint8_t cm_or_inch);
void delay_ms2(int secs);


#endif /* MEASUREDIST_H_ */
