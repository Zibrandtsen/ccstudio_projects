/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 1, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
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
#include "countled.h"

#include "gpio.h"
/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

// STOP, RED
// GET_SET, RED and YELLOW
// GO, GREEN
// HOLD, YELLOW

// NORWEGIAN_NIGHT, flash YELLOW once a second (double click)

// EMERGENCY RED (2 sec hold)

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

  // Loop forever.
  while(1) {
	// System part of the super loop.
    // ------------------------------
	while( !ticks );

	// The following will be executed every 5ms
    ticks--;

	if( ! --alive_timer )
	{
	  alive_timer        = TIM_500_MSEC;
	  GPIO_PORTD_DATA_R ^= 0x40;
	}
	
	// Application part of the super loop.
	// -----------------------------------
	event = select_button();
	operation( event );


  }
  return( 0 );
}


/****************************** End Of Module *******************************/
