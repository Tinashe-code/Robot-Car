/*
 * servo.c
 *
 *  Created on: 10 Apr,2024
 *      Author: Tinashe
 */


#define SERVO
#ifdef SERVO
#include "MKL25Z4.h" //MKL25Z4.h
#define MASK(x) (1<<x)
#include "delay.h"

#define PIN (23)  //pte
void delayms(int delay);
void period();
void Timer1();
void Timer2();
void Timer3();

int time  = 0xA30;
int time1 = 0xA30;
int time2 = 0xF5B;
int time3 = 0x1479;

void init_pin();
void Initpwm();
/*
int main(){
	Initpwm();
	init_pin();

	while(1){

		Timer1();
		delay(2);
		Timer2();
		delay(2);
		Timer3();
		delay(2);

	}

	return 0;
}

*/

void init_pin(){

	SIM->SCGC5 |=SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;

	PORTE->PCR[PIN] &= ~PORT_PCR_MUX_MASK;	//Clear mux
	PORTE->PCR[PIN] |= PORT_PCR_MUX(3);	//**setup to be output of TPM2_ch0*
}

void delayms(int delay){
	for(int x=0;x<10000*x;x++);
	/*
	 SysTick->LOAD = (20971520u/1000u)-1; //roll over every millisecond.
	 SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; //this is

	 for (int i=0; i<delay; i++){
		 unsigned int ctr=0;
	 while (1){
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk){
		ctr++; //count the milliseconds
		if(ctr==999){
		ctr=0;//one second has passed.
		break;
				}
			}
	 	 }
	 	}
	 	 SysTick->CTRL = 0; //Stop the timer
	 	 */
	}
/*
void period(){
	enum time {s1,s2,s3};
	static enum time sp = s1;

	switch(sp){
	case s1:
		Timer1();
		delay(2);
		sp = s2;
		break;
	case s2:
		Timer2();
		delay(2);
		sp = s3;
		break;
	case s3:
		Timer3();
		delay(2);
		sp = s1;

		break;
	default:
	}
}
*/
void Timer1(){
	//setting output compare
	TPM1->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM1->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM1->CONTROLS[0].CnV = 2621;
}
void Timer2(){
	//setting output compare
	TPM1->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM1->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1966;
	TPM1->CONTROLS[0].CnV = 3932;
}
void Timer3(){
	//setting output compare
	TPM1->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM1->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	TPM1->CONTROLS[0].CnV = 5243;
	//TPM2->CONTROLS[1].CnV = 2621;
}

void Initpwm(){

	//clock gating
	SIM->SCGC6 |= (1UL<<24)|(1UL<<25)|(1UL<<26); //TPM0, TPM1, TPM2
	//clock source System Option Register
	SIM->SOPT2 |= (1UL<<24);
	//Mode value
	//TPM2->MOD = 26213;
	TPM1->MOD = 52428;

	TPM1->SC |= (1UL<<7); //TOF-->
	TPM1->SC |= (1UL<<0)|(1UL<<1); //PS 3
	//TPM2->SC |= 0x2; // setting the prescalar value raised to the power of 4
	TPM1->SC |= (1UL<<6); // TOIE
	TPM1->SC |= (1UL<<3); //counter increment
/*
	//PWM + edge aligned PWM MSBA: 10, ELSBA:10, for True HIGH
	TPM2->CONTROLS[1].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1) ;
	TPM2->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK; //clear spurious interrupts
//	TPM2->CONTROLS[1].CnV =0x7FFF;
	TPM2->SC |= TPM_SC_TOF_MASK | TPM_SC_PS(7) | TPM_SC_TOIE_MASK ;
	TPM2->SC |= TPM_SC_CMOD(1); //enable internal clock to run

*/
	NVIC_ClearPendingIRQ(TPM1_IRQn);
	NVIC_SetPriority(TPM1_IRQn, 3);
	NVIC_EnableIRQ(TPM1_IRQn);
}

void TPM1_IRQHandler(){
//PWM will work even without handler.
//This handler just toggles a GPIO for purpose of comparison
//optionally check the flag
	Timer1();
			delay(200);
			Timer2();
			delay(200);
			Timer3();
			delay(200);
if (TPM1->STATUS & TPM_STATUS_CH0F_MASK){
TPM1->CONTROLS[0].CnSC |=TPM_CnSC_CHF_MASK;//clear flag
}
//PTD->PTOR |= MASK(EXT1 ) ; //THis is for debugging purposes. not needed.

TPM1->SC |= TPM_SC_TOF_MASK ; //clear the interrupt
}

#endif
