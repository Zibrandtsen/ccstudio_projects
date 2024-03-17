/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: serial.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 240321  Group 7    Module created.
*
*****************************************************************************/

#ifndef _SERIAL_H
  #define _SERIAL_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   My Functions   *******************************/

void uart0_transmit_byte(INT8U byte);
void uart0_transmit_string(INT8U *str, INT8U len);

INT8U uart0_receive_byte();
INT8U * uart0_read_message(INT8U length);


void uart0_task()

/****************************** End Of Module *******************************/
#endif

