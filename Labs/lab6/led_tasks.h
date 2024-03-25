/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _LED_TASKS_H
  #define _LED_TASKS_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/



/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void sw1_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
void red_led_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);


/****************************** End Of Module *******************************/
#endif

