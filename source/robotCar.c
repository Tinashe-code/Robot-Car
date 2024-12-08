/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "MKL25Z4.h"


#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "ConfigurePorts.h"
#include "myglcd.h"


#define MASK(x) (1UL << x)




int main(void){

// configure and initialize the LCD
	ConfigureOutputs();
	ConfigureOutputs();
	glcd_Initalize(); 			//initialize LCD


	glcd_WriteString("Test Kit");

while(1){
}
}
/*
#define pin18 (18)
#define MASK(x) (1UL << x)

int main(){

	//clock gate B
	SIM->SCGC6 |= MASK(10);
	PORTB->PCR[pin18] &=~0x700;		//clear mux
	PORTB->PCR[pin18] |=MASK(8);
	GPIOB->PDDR |= MASK(pin18);


return 0;
for(int x=0;x<l    )
}
*/
