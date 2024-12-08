/*
 * navigation.h
 *
 *  Created on: 02 Apr,2024
 *      Author: Tinashe
 */

#ifndef NAVIGATION_H_
#define NAVIGATION_H_

void forward();
void reverse();
void initialize(void);
void init_output();
void speedselect();
void speed1();
void speed2();
void speed3();
void speed4();
void speed5();
void speed6();
void speed7();
void init_ADC(void);
void voltage(void);
void left();
void right();
void stopcar(void);
void period();
void period();
void Timer1();
void Timer2();
void Timer3();
#define SETCHANNEL(x) (0xE0 | x) //to alter only ADCH channel no, preserve others
#endif /* NAVIGATION_H_ */
