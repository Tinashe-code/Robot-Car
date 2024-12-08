/*
 * beep.c
 *
 *  Created on: 08 Apr,2024
 *      Author: Tinashe
 */


#include "MKL25Z4.h"
#include "beep.h"
#define PTB3  (3)
#define MASK(X)   (1UL<<X)
void LED_Configuration(void);
void PIT_Init(void);
void PIT_StartTimer();
void delay_ms(uint32_t delay);
//void PIT_StartTimer(void);
//uint32_t delay_ms
volatile uint32_t delayFlag = 0; // Flag to indicate delay completion

static int beepspeed = 500;
static int y = 1;
//int i = 0;

/*
int main(void) {

    PIT_Init(); // Initialize PIT
    PIT_StartTimer();
    LED_Configuration();

for(int n=0;n<10000000;n++){

}

//PIT->CHANNEL[0].TCTRL &= ~MASK(31); //DISABLE TIMMER
PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK |PIT_TCTRL_TIE_MASK;
GPIOB->PDOR &=~ MASK(PTB18);
/*
    while (1) {

       // delay_ms(400); // Delay for 400 ms

      //  GPIOB->PTOR |= (1 << PTB18);
    }

    return 0;
}

*/
// now working on pit timer
void PIT_Init(void) {
   // SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; // Enable clock to PIT module
    SIM->SCGC6 |= MASK(23);  //clock gate the PIT MODULE
    // Enable PIT module, freeze PIT when debugging
    PIT->MCR = MASK(31)|(0<<30);

    PIT->CHANNEL[0].TCTRL &= ~MASK(31); //DISABLE TIMMER

   // Load timer with delay value
 //  PIT->CHANNEL[0].LDVAL = (SystemCoreClock / 1000);
   PIT->CHANNEL[0].LDVAL = (10485);
   // Enable timer and interrupts

PIT->CHANNEL[0].TCTRL |= MASK(0)|MASK(1);

// Enable PIT interrupt in NVIC
	NVIC_ClearPendingIRQ(PIT_IRQn);
  NVIC_SetPriority(PIT_IRQn, 3);
  NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_StartTimer(uint32_t delay_ms) {
/*
    PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK; // Disable timer

    // Load timer with delay value
    PIT->CHANNEL[0].LDVAL = (SystemCoreClock / 1000);
   // PIT->CHANNEL[0].LDVAL = (SystemCoreClock / 1000) * delay_ms;

    // Enable timer and interrupts
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
*/
}

void PIT_IRQHandler(void) {
static int i = 0;

//if(PIT->CHANNEL[0].TFLG & MASK(31)){
	i = i + 1;

	if(beepspeed==200){
		if(y<6){
			if(i==beepspeed){
				 GPIOB->PTOR |= (1 << PTB3);
					 i = 0;
					 y++;

				}

		}else if(y==6){
				y=1;
				stoptimmer();
		}


	}else if(beepspeed==500){
				if(i==beepspeed){
					 GPIOB->PTOR |= (1 << PTB3);
					 i = 0;
				}
	}


//}
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK; // Clear PIT flag

    delayFlag = 1; // Set delay completion flag
}

void delay_ms(uint32_t delay) {
    delayFlag = 0; // Reset delay completion flag
    PIT_StartTimer(delay); // Start PIT timer

    while (!delayFlag) {
        // Wait for delay completion
    }
}

// this code will be able to select whether the buzzer beeps fatser or slower
void beepfrequency(int freq){

	beepspeed = freq;

}



void LED_Configuration(void) {
    SIM->SCGC5 |= (1UL << 10); // Enable clock to PORTB module

    PORTB->PCR[PTB3] &=~~700UL; //clear the mux
    PORTB->PCR[PTB3] |= PORT_PCR_MUX(1); // Configure pin PTB18 as GPIO
    GPIOB->PDDR |= (1 << PTB3); // Set pin PTB18 as output
    GPIOB->PDOR |= (1 << PTB3); // Set pin PTB18 as output
    GPIOB->PDOR &=~ MASK(PTB3);
}

void stoptimmer(void){
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK |PIT_TCTRL_TIE_MASK;
	GPIOB->PDOR &=~ MASK(PTB3);

}


