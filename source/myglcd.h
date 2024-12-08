/*
 * myglcd.h
 *
 *  Created on: 25 Jan,2024
 *      Author: Tinashe
 */

#ifndef MYGLCD_H_
#define MYGLCD_H_

void glcd_data(int ASCII);
void glcd_Initalize(void);										//function to initialize lcd
void glcd_command(unsigned char cmd);							//Sending commands to screen
void glcd_screen_select(unsigned char page);					// Selecting screen 1 or screen 2
void glcd_clear_display(void);									//clearing the screen
void glcd_display(unsigned char *templ);						//display data on the screen
void glcd_GetCursor(uint8_t x_steps, uint8_t y_steps);			//function to return the current position for the cursor
void glcd_setCursor(uint8_t x, unsigned char y);				// setting the position of cursor
void glcd_WriteString(const char *str);							// Function to write data to the screen
void glcd_PageSelect(char page_num);							//selecting the page
void glcd_BackSpace(void);										// Deleting 1 character a time
void _delay_ms(float num);									// delay function
void glcd_screen_select(unsigned char page);
void glcd_clear_display();
void ReturnHome();
void MoveCursorRight();
void MoveCursorLeft();
void ShiftDisplayRight();
void ShiftDisplayLeft();
void DisplayPosition();
#endif

/* MYGLCD_H_ */
