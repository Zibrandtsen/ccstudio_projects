/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP) 2024
* Group 7
*
* MODULENAME.: main.c
*
* PROJECT....: Assignemt 2
*
* DESCRIPTION: Assignment 2, main module. No main.h file.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "systick.h"
#include "button.h"
#include "operation.h"

#include "gpio.h"
#include "lcd.h"
/*****************************    Defines    *******************************/
#define RS 0x04
#define EN 0x08

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern INT16S ticks;
/*****************************   Functions   *******************************/




int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
	INT8U event;
	INT8U operation_value;
	INT8U alive_timer = TIM_500_MSEC;

	// init_systick();
	init_gpio();
	init_LCD();


  // Loop forever.
  while(1) {
	// System part of the super loop.
    // ------------------------------
	if ((GPIO_PORTF_DATA_R & (1 << 4)) == 0) {
		GPIO_PORTF_DATA_R |= (1 << 2);

		LCD4bits_Cmd(0x80); // Set cursor to first line
		LCD_WriteString("l", 1);

		while ((GPIO_PORTF_DATA_R & (1 << 4)) == 0) {}

	} else {
		LCD4bits_Cmd(0x01); // Clear display
		GPIO_PORTF_DATA_R &= ~(1 << 2);
	}

  }
  return( 0 );
}


/****************************** End Of Module *******************************/
