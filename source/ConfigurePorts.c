/*
 * ConfigurePorts.c
 *
 *  Created on: 25 Jan,2024
 *      Author: Tinashe
 */
#define MASK(X) (1UL<<X)
#include "MKL25Z4.h"
/*
 * The following code below are the macros used to select when
 *  you want to make which pins output or input. Just uncomment
 *   any port you want to use in your code.
 */


//#define PortA_out
//#define PortB_out
#define PortC_out
#define PortD_out
//#define PortE_out

/*
 * The following code below are the macros used to select when
 *  you want to make which pins output or input. Just uncomment
 *   any port you want to use in your code.
 */
//#define PortA_in
//#define PortB_in
//#define PortC_in
//#define PortD_in
//#define PortE_in

/*
 * Write the numbers of the ports you want to configure in the array Portsx[]={};*/

void ConfigureOutputs(){
int i;
	// in this code we define how to set different ports as outputs
#ifdef PortA_out
//	Clearing configurations for all ports in port A
	 int PortsA[] = {0,1,2,3,4,5,6,7};  					// Initialize your list of numbers
	    int sizeA = sizeof(PortsA)/ sizeof(PortsA[0]);  	// Calculate the size of the list

// Iterate through the list using a for loop
	for (i = 0; i < sizeA; i++) {
		PORTA->PCR[PortsA[i]] = 0;							 	   // Clear the configure on the pins
	}

//Set the pins to output
	for (i = 0; i<sizeA; i++){
//set up pin as GPIO --> configure mux to connect pins as GPIO
		PORTA->PCR[PortsA[i]] &= ~0x700;							//PORT_PCR_MUX_MASK;	//Clear mux
		PORTA->PCR[PortsA[i]] |= (1UL<<8); 							//PORT_PCR_MUX(1);			//setup to be GPIO
		PTA->PDDR |= MASK(PortsA[i]);
	}
#endif

//configuring port B as output
#ifdef PortB_out

	//	Clearing configurations for all ports in port A
		 int PortsB[] = {0,1,2,3};  					// Initialize your list of numbers
		    int sizeB = sizeof(PortsB)/ sizeof(PortsB[0]);  	// Calculate the size of the list

	// Iterate through the list using a for loop
		for (i = 0; i < sizeB; i++) {
			PORTB->PCR[PortsB[i]] = 0;							 	   // Clear the configure on the pins
		}

	//Set the pins to output
		for (i = 0; i<sizeB; i++){
	//set up pin as GPIO --> configure mux to connect pins as GPIO
			PORTB->PCR[PortsB[i]] &= ~0x700;							//PORT_PCR_MUX_MASK;	//Clear mux
			PORTB->PCR[PortsB[i]] |= (1UL<<8); 							//PORT_PCR_MUX(1);			//setup to be GPIO
			PTB->PDDR |= MASK(PortsB[i]);
		}
#endif


#ifdef PortC_out

		//	Clearing configurations for all ports in port A
			 int PortsC[] = {0,1,2};  					// Initialize your list of numbers
				int sizeC = sizeof(PortsC)/ sizeof(PortsC[0]);  	// Calculate the size of the list

		// Iterate through the list using a for loop
			for (i = 0; i < sizeC; ++i) {
				PORTC->PCR[PortsC[i]] = 0;							 	   // Clear the configure on the pins
			}

		//Set the pins to output
			for (i = 0; i<sizeC; i++){
		//set up pin as GPIO --> configure mux to connect pins as GPIO
				PORTC->PCR[PortsC[i]] &= ~0x700;							//PORT_PCR_MUX_MASK;	//Clear mux
				PORTC->PCR[PortsC[i]] |= (1UL<<8); 							//PORT_PCR_MUX(1);			//setup to be GPIO
				PTC->PDDR |= MASK(PortsC[i]);
			}
#endif


#ifdef PortD_out

		//	Clearing configurations for all ports in port D
			 int PortsD[] = {0,1,2,3,4,5,6,7};  					// Initialize your list of numbers
				int sizeD = sizeof(PortsD)/ sizeof(PortsD[0]);  	// Calculate the size of the list

		// Iterate through the list using a for loop
			for (i = 0; i < sizeD; ++i) {
				PORTD->PCR[PortsD[i]] = 0;							 	   // Clear the configure on the pins
			}

		//Set the pins to output
			for (i = 0; i<sizeD; i++){
		//set up pin as GPIO --> configure mux to connect pins as GPIO
				PORTD->PCR[PortsD[i]] &= ~0x700;							//PORT_PCR_MUX_MASK;	//Clear mux
				PORTD->PCR[PortsD[i]] |= (1UL<<8); 							//PORT_PCR_MUX(1);			//setup to be GPIO
				PTD->PDDR |= MASK(PortsD[i]);
			}

#endif


#ifdef PortE_out

	//	Clearing configurations for all ports in port E
		 int PortsE[] = {0,1,2,3};  					// Initialize your list of numbers
			int sizeE = sizeof(PortsE)/ sizeof(PortsE[0]);  	// Calculate the size of the list

	// Iterate through the list using a for loop
		for (i = 0; i < sizeE; ++i) {
			PORTE->PCR[PortsE[i]] = 0;							 	   // Clear the configure on the pins
		}

	//Set the pins to output
		for (i = 0; i<sizeE; i++){
	//set up pin as GPIO --> configure mux to connect pins as GPIO
			PORTE->PCR[PortsE[i]] &= ~0x700;							//PORT_PCR_MUX_MASK;	//Clear mux
			PORTE->PCR[PortsE[i]] |= (1UL<<8); 							//PORT_PCR_MUX(1);			//setup to be GPIO
			PTE->PDDR |= MASK(PortsE[i]);
		}
#endif

}


void ConfigureInputs(){
	int i;

	//	We configure the input Ports remembering to use the the pull up resistors
#ifdef PortA_in
int PortsA[] = {0,1,2,3,4,5,6,7};  					// Initialize your list of numbers
int sizeA = sizeof(PortsA)/ sizeof(PortsA[0]);  	// Calculate the size of the list


/*Iterate through the list using a for loop. At this point
* we iterate over the selected pins configuring them as inputs
* and enabling the pull up resistors
* */
for (i = 0; i < sizeA; ++i) {

	PORTA->PCR[PortsA[i]] = 0;							 	   // Clear the configure on the pins
}
for (i = 0; i < sizeA; ++i) {

		PORTA->PCR[PortsA[i]] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

	}
#endif

#ifdef PortB_in
int PortsB[] = {0,1,2,3,4,5,6,7};  					// Initialize your list of numbers
int sizeB = sizeof(PortsB)/ sizeof(PortsB[0]);  	// Calculate the size of the list


/*Iterate through the list using a for loop. At this point
* we iterate over the selected pins configuring them as inputs
* and enabling the pull up resistors
* */
for (i = 0; i < sizeB; ++i) {

	PORTB->PCR[PortsB[i]] = 0;							 	   // Clear the configure on the pins
}
for (i = 0; i < sizeE; ++i) {

		PORTB->PCR[PortsB[i]] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

	}
#endif

#ifdef PortC_in
int PortsC[] = {0,1,2,3};  					// Initialize your list of numbers
int sizeC = sizeof(PortsC)/ sizeof(PortsC[0]);  	// Calculate the size of the list


/*Iterate through the list using a for loop. At this point
* we iterate over the selected pins configuring them as inputs
* and enabling the pull up resistors
* */
for (i = 0; i < sizeC; ++i) {

	PORTC->PCR[PortsC[i]] = 0;							 	   // Clear the configure on the pins
}
for (i = 0; i < sizeC; ++i) {

		PORTC->PCR[PortsC[i]] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

	}
#endif

#ifdef PortD_in
int PortsD[] = {0,1,2,3,4,5,6,7};  					// Initialize your list of numbers
int sizeD = sizeof(PortsD)/ sizeof(PortsD[0]);  	// Calculate the size of the list


/*Iterate through the list using a for loop. At this point
* we iterate over the selected pins configuring them as inputs
* and enabling the pull up resistors
* */
for (i = 0; i < sizeD; ++i) {

	PORTD->PCR[PortsD[i]] = 0;							 	   // Clear the configure on the pins
}
for (i = 0; i < sizeD; ++i) {

		PORTD->PCR[PortsD[i]] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

	}
#endif

#ifdef PortE_in
int PortsE[] = {0,1,2,3,4,5,6,7};  					// Initialize your list of numbers
int sizeE = sizeof(PortsE)/ sizeof(PortsE[0]);  	// Calculate the size of the list


/*Iterate through the list using a for loop. At this point
* we iterate over the selected pins configuring them as inputs
* and enabling the pull up resistors
* */
for (i = 0; i < sizeE; ++i) {

	PORTE->PCR[PortsE[i]] = 0;							 	   // Clear the configure on the pins
}
for (i = 0; i < sizeE; ++i) {

		PORTE->PCR[PortsE[i]] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

			}
#endif

}


//end
