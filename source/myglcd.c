/*
 * myglcd.c
 *
 *  Created on: 25 Jan,2024
 *      Author: Tinashe Kanukai
 *      In this C file we are going to define all the functions that we will use to write to the LCD.
 *      ALL the C code will be defined in this code.
 */

/*
 * this project will be based on the NXP microcontrollers so the registers used will be based on KL25Z
 * Below is the definition of the ports that will be use and the registers
 */

#include "MKL25Z4.h"
#include "fsl_gpio.h"  // Include the GPIO header file for your specific NXP microcontroller
#include "board.h"
#include "myglcd.h"

/*
 *For this part we are going to be defining all the registers we need for this LCD TO
 *For work. For our case we are going to use port de
 */


#define glcd_data_port GPIOD->PDOR
#define glcd_control_port GPIOC->PDOR  //changed from B
#define glcd_cport_dir GPIOC->PDDR	//CHanged from b
#define glcd_dport_dir GPIOD->PDDR
#define ClearOutPort GPIOD->PCOR

#define RS  (1<<0)
#define RW  (1<<1)
#define E   (1<<2)


/*
 * Below are the values in Hex to light and print different
 * characters on the screen. The roles are arranged in ASCII
 * number order of different characters. So each role
 * represents a character that is printable on the screen
 * */

int asciiValues[128] = {
	    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
	    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
	    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
	    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
	    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
	};

void _delay_ms(float num){
	for (int i=0; i<(1000*num); i++);
}

void glcd_command(unsigned char cmd){    //recently made changes
	glcd_data_port = 0;								//clearing data PORT *******
	glcd_data_port |= cmd;							//sending command****************8
	glcd_control_port &= ~RS;						// setting register at zero to accept commands
	glcd_control_port &= ~RW;						// 0 for write
	glcd_control_port |= E;							//High pulse
	_delay_ms(0.1);
	glcd_control_port &= ~E;						//Low pulse
}

int count = 0;
void glcd_WriteString(const char *str){
	 if (str == NULL) {
	        return;
	    }
	    while (*str != '\0') {
	        int a = *str;
	        glcd_data(a);
	        str++;
	        count++;
	        if (count == 16){
	        	if(a == 32){
	        	glcd_data(a);
	        	}
	        	glcd_command(0xC0);
//	        	DisplayPosition(count);
	        }
	    }
}

void glcd_clear_display(){
//		delay(2);
		glcd_command(0x01);								// clearing the whole display
//		delay(2);
		glcd_command(0x02);
}

void ReturnHome(){
		glcd_command(0x02);								// setting the cursor to 00
}

void MoveCursorRight(){
		glcd_command(0x06);								// Moving the cursor to the right
}
void MoveCursorLeft(){
		glcd_command(0x04);								// moving and blinking the cursor to the left
}

void ShiftDisplayRight(){
		glcd_command(0x05);								// moving cursor to the right
}

void ShiftDisplayLeft(){
		glcd_command(0x07);								// =shifting the screen to the left
}


void DisplayPosition(int num){
	const char* position[] = {
	        "0x00", "0x01", "0x02", "0x03", "0x04", "0x05", "0x06", "0x07",
	        "0x08", "0x09", "0x0A", "0x0B", "0x0C", "0x0D", "0x0E", "0x0F",
	        "0x40", "0x41", "0x42", "0x43", "0x44", "0x45", "0x46", "0x47",
	        "0x48", "0x49", "0x4A", "0x4B", "0x4C", "0x4D", "0x4E", "0x4F"
	    };
	glcd_command(position[num]);
}

void glcd_Initalize(){
	/* initializing the LCD and setting
	the states of the input and output pins
	*/

	_delay_ms(1);
	glcd_control_port &= ~RW;
	glcd_control_port &= ~RS;
	glcd_control_port &= ~E;
	_delay_ms(1);
	glcd_command(0x0F);								// turning LCD ON
	_delay_ms(1);
	glcd_command(0x80);								// select column zero. first box of the first column
	_delay_ms(1);
	glcd_command(0x3F);								// Selecting 8 bit input mode. and selecting two line display mode with 5x8 bits mode
	_delay_ms(1);
	glcd_clear_display();
	_delay_ms(1);
	ReturnHome();
}

void glcd_data(int ASCII){
	ClearOutPort |= 0xFF;							//clearing the output port
	glcd_data_port |= asciiValues[ASCII];
	glcd_control_port &=~ RW;
	glcd_control_port |= RS;						// setting the register pin 1 for sending data to screen
	//the enable pin must produce a high-low pulse to latch the data on the data pins

	glcd_control_port |= E;							//set enable high
	_delay_ms(1);									// the value of this display affects how the data is displayed on the screen
	glcd_control_port &= ~E;						//set enable low
}
