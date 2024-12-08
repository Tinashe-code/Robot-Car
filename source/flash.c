/*
 * flash.c
 *
 *  Created on: 08 Apr,2024
 *      Author: Tinashe
 */

#include "navigation.h"
#include <mkl25z4.h>
#include <stdint.h>
#include <stdio.h>


#define RED_LED (3)
#define BLUE_LED (4)

#define MASK(x) (1UL << x)
/*
int main(){
//init_LED();
init_Timer();
while(1){}
}
*/
void init_Timer(){
//Clock gate
	SIM->SCGC6 |=SIM_SCGC6_TPM0_MASK;
	//Select clock source in SIM_SOPT
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); //1- MCGPLLCLK/2,
	//Configure registers
	//TPM0->MOD= 0xFFFF;
	TPM0->MOD= 32767;

	//TPM0->MOD= (20971520/32)*1000 - 1;
	TPM0->SC |= TPM_SC_TOF_MASK; //Clear TOF before start,
	TPM0->SC |= TPM_SC_PS(7); //optional pre-scale by 2^5 =32
	TPM0->SC |= TPM_SC_TOIE_MASK; //Enable TOIE for interrupt
	TPM0->SC |= TPM_SC_CMOD(1); //enable internal clock to run
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_SetPriority(TPM0_IRQn, 3);
	NVIC_EnableIRQ(TPM0_IRQn);

}
//TPM0->SC |= TPM_SC_TOF_MASK | TPM_SC_PS(5) | TPM_SC_TOIE_MASK |TPM_SC_CMOD(1);
//alternative format
void TPM0_IRQHandler(){
static int ctr=1;
static int n = 0;
n++;
if(n==1){
if (ctr==1){

GPIOC->PDOR &=~MASK(BLUE_LED);
PTC->PTOR |= MASK(RED_LED); //Toggle PTB18

//ctr=0;
//ctr++;
}else if(ctr >1 && ctr <8){
	GPIOC->PDOR &=~MASK(RED_LED);
	//switch on the blue and then set cntr to zero
	PTC->PTOR |= MASK(BLUE_LED); //Toggle PTB18

	if(ctr==7){
		ctr=0;
	}
	//ctr = 0;
}
ctr++;
n =0;
}
TPM0->SC |= TPM_SC_TOF_MASK ; //clear the interrupt
}




