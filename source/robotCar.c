/*
* Copyright 2016-2024 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**
* @file    AssemblyClass.c
* @brief   Application entry point.
*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
extern int maxFxn(int a, int b, int c);
extern int greatest();
extern int fxn4();
extern int maxarray();
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "ConfigurePorts.h"
#include "myglcd.h"
#include "flash.h"
#include "navigation.h"
#include "FreeRTOS.h"
#include "task.h" //to create tasks
#include "robotcar.h"
#include "delay.h"
#include "MeasureDist.h"
#include "beep.h"
#include <mkl25z4.h>
#include "servo.h"
/*
* Copyright 2016-2024 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**
* @file    robotCar.c
* @brief   Application entry point.
*/
/* TODO: insert other include files here. */
#define ENABLE_WDOG_REFRESH 0 //with 0, WDT will not be refreshed.
/* TODO: insert other definitions and declarations here. */
/*
* @brief   Application entry point.
*/
#define MASK(x) (1UL << x)
#define RX 1 //PTA1
#define TX 2 //PTA2
#define OSR 15 //over sample rate (like a pre-scaler)
#define BAUD_RATE 9600 //my communication rate on BT
#define CLOCK 20971520u //our current board clock
#define BLUE 1
#define RED 18
#define GREEN 19
volatile char rxChar;
volatile char txChar;
int done =1; //to track if there is any char to transmit.
//done=1 means no more chars to transmit, disable transmitter
//volatile char rxChar; //char rx over BT
void init_pins(void);
void init_UART(void);
void init_LEDs(void);
void Init_LEDs(void);
void getcommand(void);
void init_systick(void);

int main(void){
	initialize();
	initializeCar();
	init_pins();
	init_UART();
	init_LEDs();
	PIT_Init();
	LED_Configuration();
	init_ADC();
	init_pin();
	Initpwm();
	testcar();
while(1){

}


void testcar(void){
		init_Timer(); //// for the flash light
		speed7();
		delay(10);
		 delay(1000);
		right();
		 delay(100);
		forward();
		 delay(100);
		left();
		 delay(100);
		reverse();
//
		 delay(100);
		left();
		 delay(100);
		forward();
		 delay(100);
		right();
		 delay(100);
		stopcar();
}
void initializeCar(){
	SIM->SCGC5|= (1UL<<9); //gate ports  A
		SIM->SCGC5|= (1UL<<10); //gate ports B
		SIM->SCGC5|= (1UL<<11); //gate ports C
		SIM->SCGC5|= (1UL<<12); //gate ports D
		SIM->SCGC5|= (1UL<<13); //gate ports E
		ConfigureOutputs();
		ConfigureInputs();
	//	_delay_ms(10);
		//The following function will initialize and configure your lcd
		glcd_Initalize();
		//delay(10);
		 glcd_clear_display();
			//glcd_WriteString("123456798 ");
		glcd_WriteString("*Initializing..*");
		// for the car from navigation.c
		initialize();
		init_output();
		//  TPM2_Delay_Init();
		//  PIT_Init();
}
/*
void init_systick(void){
SysTick->LOAD = (20971520u/2u)-1 ; //configure for every half sec restart.
SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk |
SysTick_CTRL_ENABLE_Msk |SysTick_CTRL_TICKINT_Msk;
}
void SysTick_Handler(){ //Timer Interrupt Service Routine ISR
static int ctr=0;
ctr++;
txChar=(ctr % 26)+97; //just to get a-z in series
send();
}
*/
void init_pins(void){
//Clock gate port A
SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
PORTA->PCR[RX] &= ~PORT_PCR_MUX_MASK; //clear mux
PORTA->PCR[RX] |= PORT_PCR_MUX(2); //set for UART0 RX
PORTA->PCR[TX] &= ~PORT_PCR_MUX_MASK; //clear
PORTA->PCR[TX] |= PORT_PCR_MUX(2); //set for UART0 TX
}
void init_UART(void){
		//select clock for uart0, MCGFLLCLK/system clk as UART0 clock
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
		// clock gate UART0
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //clock gate UART0
		//compute set baud rate (SBR), choosing baud rate of 9600 for BT
		uint8_t sbr = (uint16_t)((CLOCK)/((OSR+1) *BAUD_RATE ));
		UART0->BDH =0; //0x0 for this calculation, other fields are default 0.
		UART0->BDL=sbr; //0x88 for this calculation
		// both Rx and Tx Interrupt enabled
		UART0->C2 |= UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK ;
		//note: C1 settings unchanged. Default is 8N1 if uart0->C1=0
		NVIC_SetPriority(UART0_IRQn, 3);
		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_EnableIRQ(UART0_IRQn);
}
void init_LEDs(void) {
		// Clock gate ports B (red+green) and D (blue)
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
		//set up mux for leds. Blue is on port D. Make output
		PORTD->PCR[BLUE] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[BLUE] |= PORT_PCR_MUX(1);
		PTD->PDDR |= MASK(BLUE); //direction is output
		PORTB->PCR[RED] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[RED] |= PORT_PCR_MUX(1);
		PORTB->PCR[GREEN] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[GREEN] |= PORT_PCR_MUX(1);
		PTB->PDDR |= MASK(RED) | MASK(GREEN); //output
}
void Command(void){
		//turn off all leds
		switch (rxChar){
		case 'b':
				reverse();
				break;
		case 'f':
				forward();
				break;
		case 'r':
				right();
				break;
		case 'l':
				left();
				break;
		case 's':
				testcar();
				break;
		case 't':
				stopcar();
			//	initializeCar();
			//	testcar();
				break;
		case 'u':
			testcar();
				//speedselect(voltage());
		default:
				//forward();
		}
}
void lightLED(void){
		//turn off all leds
		PTB->PSOR = MASK(RED);
		PTB->PSOR = MASK(GREEN);
		PTD->PSOR = MASK(BLUE);
		switch (rxChar){
		case 'r':
		PTB->PCOR = MASK(RED);
		break;
		case 'g':
		PTB->PCOR = MASK(GREEN);
		break;
		case 'b':
		PTD->PCOR = MASK(BLUE);
		break;
		case 'y':
		PTB->PCOR = MASK(RED);
		PTB->PCOR = MASK(GREEN);
		//Control_RGB_LEDs(1,1,0);
		break;
		case 'p':
		PTB->PCOR = MASK(RED);
		PTD->PCOR = MASK(BLUE);
		//Control_RGB_LEDs(1,0,1);
		break;
		case 'c':
		PTB->PCOR = MASK(GREEN);
		PTD->PCOR = MASK(BLUE);
		//Control_RGB_LEDs(0,1,1);
		break;
		default:
		PTB->PCOR = MASK(RED);
		PTB->PCOR = MASK(GREEN);
		PTD->PCOR = MASK(BLUE);
		}
}

void UART0_IRQHandler(void) {
		uint8_t ch;
		if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
		UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;
		}
		if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		ch = UART0->D;
		rxChar=ch; //to enable me take some action
		Command();
		//speedselect(voltage());
		}
		
		//deal with transmission
		if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
		(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character
		if (!done) {
		UART0->D = txChar;
		done=1;
} else {
		// 1-char queue is empty so disable transmitterinterrupt
		UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}


void send(void){
		// start transmitter interrupts if it isn’t already running
		if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
		//UART0->D = x;
		done=0;
		UART0->C2 |= UART0_C2_TIE_MASK;
}
}
/*
void init_systick(void){
SysTick->LOAD = (20971520u/2u)-1 ; //configure for every half sec restart.
SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk |
SysTick_CTRL_ENABLE_Msk |SysTick_CTRL_TICKINT_Msk;
}
void SysTick_Handler(){ //Timer Interrupt Service Routine ISR
static int ctr=0;
ctr++;
//txChar=(ctr % 26)+97; //just to get a-z in series
//send();
}
*/

