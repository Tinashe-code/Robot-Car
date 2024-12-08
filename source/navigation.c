/*
 * navigation.c
 *
 *  Created on: 02 Apr,2024
 *      Author: Tinashe
 */

#include "global.h"
#include "navigation.h"
#include <mkl25z4.h>
#include <stdint.h>
#include <stdio.h>
#include "beep.h"
#include "MKL25Z4.h"
#include "delay.h"
#include "MeasureDist.h"
#include "myglcd.h"


#define MASK(x)  (1UL << x)
#define PTE20 (20)

char buff[20];
volatile int g_sample=0; //the ADC value read in interrupt
#define SETCHANNEL(x) (0xE0 | x) //to alter only ADCH channel no, preserve others
#define PTE20 (20)
void init_ADC();
float val;
#define PTB3 (3)

// use the following to define the names of the pins used to drive the motor
#define motordriver (2) //PTB2
#define motorleft1 (0)
#define motorleft2 (1)
#define motorright1 (8)
#define motorright2 (9)

// define the forward and reverse LEDs
#define reverseLED (10)
#define forwardLED (11)
#define PIN 23
static int status = 3;
int speedpoint = 7;
// code to move the folder backward
void forward(){

	glcd_clear_display();

	delay(1);

	glcd_WriteString("forward");
// To reverse intercange the ground and power going to the motor
	status = 1;
	GPIOB->PDOR |= MASK(motorleft1);
	GPIOB->PDOR &=~ MASK(motorleft2);

	// changing direction for the left motor
	GPIOB->PDOR |= MASK(motorright1);
	GPIOB->PDOR &=~ MASK(motorright2);

	GPIOB->PDOR |= MASK(forwardLED);
	GPIOB->PDOR &=~ MASK(reverseLED);

	//PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK |PIT_TCTRL_TIE_MASK;
	//GPIOB->PDOR &=~ MASK(PTB3);
	stoptimmer();
}



//This is the code to move the robot in reverse or in forward mode.
void reverse(){
	glcd_clear_display();

		delay(1);

		glcd_WriteString("reverse");
	status = 0;
//changing the direction for the left motor
	GPIOB->PDOR |= MASK(motorleft2);
	GPIOB->PDOR &=~ MASK(motorleft1);

	// changing direction for the left motor
	GPIOB->PDOR |= MASK(motorright2);
	GPIOB->PDOR &=~ MASK(motorright1);

	GPIOB->PDOR &=~ MASK(forwardLED);
	GPIOB->PDOR |= MASK(reverseLED);
	beepfrequency(500);
	PIT_Init();
//	PIT_StartTimer();
	LED_Configuration();
}


void left(){


	if(status==0){
		//forward();
		reverse();
	}else if(status==1){
		forward();
		//reverse();
	}

	glcd_clear_display();

			delay(1);

			glcd_WriteString("left");
	//Stop the left wheel from rotating
	GPIOB->PDOR &=~ MASK(motorleft1);
	GPIOB->PDOR &=~ MASK(motorleft2);


}

void right(){

	if(status==0){
			//forward();
			reverse();
		}else if(status==1){
			forward();
			//reverse();
		}

	glcd_clear_display();

			delay(10);

			glcd_WriteString("right");
	// stop the right wheel from rotating
	GPIOB->PDOR &=~ MASK(motorright1);
	GPIOB->PDOR &=~ MASK(motorright2);

}

void stopcar(void){
	glcd_clear_display();

		delay(10);

		glcd_WriteString("stop");
	status = 3;
	GPIOB->PDOR &=~ MASK(motorleft1);
	GPIOB->PDOR &=~ MASK(motorleft2);

	// changing direction for the left motor
	GPIOB->PDOR &=~ MASK(motorright1);
	GPIOB->PDOR &=~ MASK(motorright2);

	GPIOB->PDOR &=~ MASK(forwardLED);
	GPIOB->PDOR &=~ MASK(reverseLED);
	stoptimmer();
}


// this function will select. This will used anologue to digital converter to change the speed
void speedselect(int sp){

	while(1){

	}
	enum time {s1=1,s2=2,s3=3,s4=4,s5=5,s6=6,s7=7};

		switch(sp){
		case s1:
					speed1();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("Speed 1");
					break;
		case s2:
					speed2();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed2");
					break;
		case s3:
					speed3();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed3");
					break;
		case s4:
					speed4();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed4");
					break;
		case s5:
					speed5();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed5");
					break;
		case s6:
					speed6();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed6");
					break;
		case s7:
					speed7();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed7");
					break;
		default:
					speed7();
					glcd_clear_display();

						delay(10);

						glcd_WriteString("speed8");
					break;
		}

}


void speed1(){

	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 10485;
/*
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[1].CnV = 10485;
	*/
}
void speed2(){

	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 26214;
/*
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1966;
	TPM2->CONTROLS[1].CnV = 26214;
	*/
}
void speed3(){
	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 31457;

/*
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	TPM2->CONTROLS[1].CnV = 5243;
	//TPM2->CONTROLS[1].CnV = 31457;
	 *
	 */
}

void speed4(){

	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 36700;

/*
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[1].CnV = 36700;
	*/
}
void speed5(){


	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 41943;

/*
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1966;
	TPM2->CONTROLS[1].CnV = 41943;
	*/
}
void speed6(){
	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 47185;

/*
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	TPM2->CONTROLS[1].CnV = 5243;
	//TPM2->CONTROLS[1].CnV = 47185;
	 * *
	 */
}

void speed7(){
	//setting output compare

	TPM2->CONTROLS[0].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[0].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[0].CnV = 52428;
/*
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[1].CnV = 52428;
	*/
}


/*
void Timer1(){
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1310;
	TPM2->CONTROLS[1].CnV = 2621;
}
void Timer2(){
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	//TPM2->CONTROLS[1].CnV = 1966;
	TPM2->CONTROLS[1].CnV = 3932;
}
void Timer3(){
	//setting output compare
	TPM2->CONTROLS[1].CnSC |= (1UL<<5)|(1UL<<3); //PWM. MSnB and ELSnB
	TPM2->CONTROLS[1].CnSC |= (1UL<<7); //clear any spurious interrupts CHF
	TPM2->CONTROLS[1].CnV = 5243;
	//TPM2->CONTROLS[1].CnV = 2621;
}

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
void initialize(void){
	//clock gate TPM0



	//clock gating
		SIM->SCGC6 |= (1UL<<24)|(1UL<<25)|(1UL<<26); //TPM0, TPM1, TPM2
		//clock source System Option Register
		SIM->SOPT2 |= (1UL<<24);
		//Mode value
		//TPM2->MOD = 26213;
		TPM2->MOD = 52428;

		TPM2->SC |= (1UL<<7); //TOF-->
		TPM2->SC |= (1UL<<0)|(1UL<<1); //PS 3
		//TPM2->SC |= 0x2; // setting the prescalar value raised to the power of 4
		TPM2->SC |= (1UL<<6); // TOIE
		TPM2->SC |= (1UL<<3); //counter increment


		NVIC_ClearPendingIRQ(TPM2_IRQn);
		NVIC_SetPriority(TPM2_IRQn, 3);
		NVIC_EnableIRQ(TPM2_IRQn);
}


void TPM2_IRQHandler(){
//PWM will work even without handler.
//This handler just toggles a GPIO for purpose of comparison
//optionally check the flag
	Timer1();
			delay(2);
			Timer2();
			delay(2);
			Timer3();
			delay(2);
if (TPM2->STATUS & TPM_STATUS_CH0F_MASK){
TPM2->CONTROLS[1].CnSC |=TPM_CnSC_CHF_MASK;//clear flag
}
//PTD->PTOR |= MASK(EXT1 ) ; //THis is for debugging purposes. not needed.

TPM2->SC |= TPM_SC_TOF_MASK ; //clear the interrupt
}



// configure the output pin for driving the motor
void init_output(){
	SIM->SCGC5 |=SIM_SCGC5_PORTB_MASK;
	//left motor

	PORTB->PCR[motordriver] &= ~PORT_PCR_MUX_MASK; //Clear mux
	PORTB->PCR[motordriver] |= PORT_PCR_MUX(3);// setup to be output of TPM2_CH0

	//right motor
	//PORTB->PCR[motordriver] &= ~PORT_PCR_MUX_MASK; //Clear mux
	//PORTB->PCR[motordriver] |= PORT_PCR_MUX(3);// setup to be output of TPM2_CH0

	//Initilise the pins for forwad and reverse indication as gpio output or input

	PORTB->PCR[reverseLED] &=~ 0x700; //Clear mux
	PORTB->PCR[reverseLED] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= MASK(reverseLED);

	PORTB->PCR[forwardLED] &=~ 0x700; //Clear mux
	PORTB->PCR[forwardLED] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= MASK(forwardLED);

	PORTB->PCR[motorleft1] &=~ 0x700; //Clear mux
	PORTB->PCR[motorleft1] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= MASK(motorleft1);

	PORTB->PCR[motorleft2] &=~ 0x700; //Clear mux
	PORTB->PCR[motorleft2] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= MASK(motorleft2);

	PORTB->PCR[motorright2] &=~ 0x700; //Clear mux
	PORTB->PCR[motorright2] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= MASK(motorright2);

	PORTB->PCR[motorright1] &=~ 0x700; //Clear mux
	PORTB->PCR[motorright1] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= MASK(motorright1);

	SIM->SCGC5 |=SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;

	//PORTE->PCR[PIN] &= ~PORT_PCR_MUX_MASK;	//Clear mux
	//PORTE->PCR[PIN] |= PORT_PCR_MUX(3);	//**setup to be output of TPM2_ch0*

}



void init_ADC(void) {
SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
// Select analog for pin
PORTE->PCR[PTE20] &= ~PORT_PCR_MUX_MASK;
PORTE->PCR[PTE20] |= PORT_PCR_MUX(0);
//16 bit single-ended conversion, when DIFF=0
ADC0->CFG1 |= ADC_CFG1_MODE(3);
ADC0->SC1[0] |= ADC_SC1_AIEN_MASK ;// ******enable interrupts

NVIC_ClearPendingIRQ(ADC0_IRQn);
NVIC_SetPriority(ADC0_IRQn, 3);
NVIC_EnableIRQ(ADC0_IRQn);


}


// try putting the speed select funtion here
void ADC0_IRQHandler(void){
if (ADC0->SC1[0] & ADC_SC1_COCO_MASK){
g_sample = ADC0->R[0];
//flag is cleared when data is read.
ADC0->SC1[0] &= SETCHANNEL(0); // SW trigger + start conversion on ADCH 0,
//ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(0); //ALT method


}

//speedselect(voltage());
}
/*
int voltage(void){
	val = (float)3.3*g_sample/0xffff; //recall 0xffff maps to max of3.3v
	printf("%X\n",g_sample); //cannot print float on MCU
	int whole=val;
	float fraction = val-whole;
	int decimal= fraction*10000; //working to 4 decimal places
	sprintf(buff,"Voltage= %2d.%04d", whole, decimal);
	printf("%s\n", buff);

	float speed_value = val;

	 if (speed_value >= 0 && speed_value <= 0.47) {
	        return 1;

	    } else if (speed_value >= 0.48 && speed_value <= 0.94) {
	       return 2;
	    } else if (speed_value >= 0.95 && speed_value <= 1.41) {
	       return 3;
	    } else if (speed_value >= 1.42 && speed_value <= 1.88) {
	        return 4;
	    } else if (speed_value >= 1.89 && speed_value <= 2.35) {
	        return 5;
	    } else if (speed_value >= 2.36 && speed_value <= 2.82) {
	       return 6;
	    } else if (speed_value >= 2.83 && speed_value <= 3.30) {
	        return 7;
	    } else {
	       return 0;
	    }
}
*/

void voltage(void){
	g_sample = ADC0->R[0];
	val = (float)3.3*g_sample/0xffff; //recall 0xffff maps to max of3.3v
	printf("%X\n",g_sample); //cannot print float on MCU
	int whole=val;
	float fraction = val-whole;
	int decimal= fraction*10000; //working to 4 decimal places
	sprintf(buff,"Voltage= %2d.%04d", whole, decimal);
	printf("%s\n", buff);

	float speed_value = val;

	 if (speed_value >= 0 && speed_value <= 0.47) {
		 printf("voltage one\n");
		 speedpoint = 1;
		// break;
	       // return 1;

	    } else if (speed_value >= 0.48 && speed_value <= 0.94) {
	    	speedpoint = 2;
	    //	break;
	     //  return 2;
	    } else if (speed_value >= 0.95 && speed_value <= 1.41) {
	    	speedpoint = 3;
	    //	break;
	      // return 3;
	    } else if (speed_value >= 1.42 && speed_value <= 1.88) {
	    	speedpoint = 4;
	    //		    	break;
	      //  return 4;
	    } else if (speed_value >= 1.89 && speed_value <= 2.35) {
	    	speedpoint = 5;
	    	//	    	break;
	       // return 5;
	    } else if (speed_value >= 2.36 && speed_value <= 2.82) {
	    	speedpoint = 6;
	    	//	    	break;
	    //   return 6;
	    } else if (speed_value >= 2.83 && speed_value <= 3.30) {
	    	printf("voltage 7\n");
	    	speedpoint = 7;
	    //		    	break;
	     //   return 7;
	    } else {
	    //	speedpoint = 3;
	    //		    	break;
	      // return 0;
	    }
}

