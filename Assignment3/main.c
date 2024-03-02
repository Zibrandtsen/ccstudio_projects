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

	init_systick();
	init_gpio();
	init_LCD();
	// LCD4bits_Cmd(0x01);
	// LCD4bits_Cmd(0x80);

  // Loop forever.
  while(1) {
	// System part of the super loop.
    // ------------------------------
	// while( !ticks );

	// // The following will be executed every 5ms
    // ticks--;

	// if( ! --alive_timer )
	// {
	//   alive_timer        = TIM_500_MSEC;
	//   GPIO_PORTD_DATA_R ^= 0x40;
	// }
	
	// Application part of the super loop.
	// -----------------------------------
	
	// event = select_button();
	// operation( event );

	// ------------------------------
	// GPIO_PORTC_DATA_R = 0x40;	// 0100
	// GPIO_PORTD_DATA_R |= EN;	// Enable E

	// GPIO_PORTC_DATA_R = 0x10;	// 0001
	// ------------------------------

	LCD_Write4bits( 0x00, 0x00);
	LCD_Write4bits( 0x10, 0x00);
	delayUs(40);	//delay for LCD (MCU is faster than LCD)

	// ------------------------------



	// writeChar( 0xC, 0xC );
	// writeCommand( 0xB );
	// char* str = "Tiva C Projects";
	// LCD_WriteString(str);

  }
  return( 0 );
}


/****************************** End Of Module *******************************/
