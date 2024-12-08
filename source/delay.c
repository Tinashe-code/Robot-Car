/*
 * delay.c
 *
 *  Created on: 08 Apr,2024
 *      Author: Tinashe
 */




#include "MKL25Z4.h"
#include "delay.h"


void delay(int n){

	for(int h=0;h<10000*n;h++){}

}

/*

void TPM2_Delay_Init() {
    // Enable clock to TPM2 module
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

    // Configure TPM2 for overflow every millisecond
    TPM2->SC = TPM_SC_PS(5); // Prescale by 32
    TPM2->MOD = 65535; // Set modulo register for maximum value

    // Use internal clock as clock source, count up, and enable interrupts
    TPM2->SC |= TPM_SC_CMOD(1) | TPM_SC_TOIE_MASK;

    // Enable TPM2_IRQn interrupt vector in NVIC
  //  NVIC_EnableIRQ(TPM2_IRQn);
    NVIC_ClearPendingIRQ(TPM2_IRQn);
    NVIC_SetPriority(TPM2_IRQn, 3);
    NVIC_EnableIRQ(TPM2_IRQn);
}

void TPM2_IRQHandler() {
    // Clear TPM2 overflow interrupt
    TPM2->SC |= TPM_SC_TOF_MASK;
}

void TPM2_Delay_Milliseconds(uint32_t milliseconds) {
    // Reset counter
	TPM2->CNT = 0;

    // Wait until counter reaches desired value
    while (TPM2->CNT < milliseconds) {}


}



int main() {
    TPM2_Delay_Init();

    // Use the delay function
    TPM2_Delay_Milliseconds(1000); // Delay for 1000 milliseconds (1 second)

    // Other code...

    return 0;
}
*/
