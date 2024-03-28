/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: keypad.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Keypad functionality.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 240325  JRZ    Module created.
*
*****************************************************************************/

#ifndef _KEYPAD_H
  #define _KEYPAD_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void keypad_task(INT8U id, INT8U state, INT8U event, INT8U data);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
void keypad_task2(INT8U my_id, INT8U my_state, INT8U event, INT8U data);

/****************************** End Of Module *******************************/
#endif

