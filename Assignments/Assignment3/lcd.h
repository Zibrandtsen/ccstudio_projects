/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
* Group 7
*
* MODULENAME.: operation.h
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: Test.
*
*
*****************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void init_LCD( void );
INT8U clearDisplay( INT8U );
INT8U setCursor( INT8U );
INT8U writeString( INT8U );

void LCD4bits_Data(unsigned char data);

void LCD_Write4bits( unsigned char data, unsigned char control );
void LCD4bits_Cmd( unsigned char command );

void LCD_WriteString(INT8U * str, INT8U len);

void delayMs(int n);
void delayUs(int n);

void delay(volatile int time);

/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : -
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*LCD_H_*/
