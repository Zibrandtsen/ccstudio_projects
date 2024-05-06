/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
* Group 7
*
* MODULENAME.: operation.c
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: See module specification file (.h-file).
*
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "swtimers.h"
#include "lcd.h"
/*****************************    Defines    *******************************/
#define RS 0x04 // PD2
#define EN 0x08 // PD3


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_LCD(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD;

    // Enable clock to GPIO Port C  // page 339 - Tiva
    SYSCTL_RCGCGPIO_R |= 0x0C;      // bit placement
                                    // bit 0: Port A: 0x01
                                    // bit 1: Port B: 0x02
                                    // bit 2: Port C: 0x04
                                    // bit 3: Port D: 0x08
    delayMs(10);

    // Set the direction as output.
    GPIO_PORTC_DIR_R = 0xF0;   // PC4, PC5, PC6, PC7
    GPIO_PORTD_DIR_R = 0x0C;   // PD2(RS), PD3(E)

    // Enable the GPIO pins for digital function.
    GPIO_PORTC_DEN_R = 0xF0;
    GPIO_PORTD_DEN_R = 0x0C;

    LCD4bits_Cmd(0x28);         // 2 lines and 5x7 character (4-bit data, D4 to D7)
    LCD4bits_Cmd(0x06);         // Automatic Increment cursor (shift cursor to right)
    LCD4bits_Cmd(0x0C);         // Display on, cursor blinking
    LCD4bits_Cmd(0x01);         // Clear display screen
}

void LCD_Write4bits( unsigned char data, unsigned char control )
/*****************************************************************************
*   Input    : -
*   Output   : - 
*   Function : - 
******************************************************************************/
{
    // GPIO_PORTC_DATA_R = 0x00;
    data &= 0xF0;       // Clear lower 4 bits
    control &= 0x0F;    // Clear upper 4 bits

    GPIO_PORTC_DATA_R = data; // write data

    GPIO_PORTD_DATA_R |= control;
    GPIO_PORTD_DATA_R |= EN;
    // delayUs(250);
    delay(7000);
    GPIO_PORTD_DATA_R &= ~EN;
    // GPIO_PORTD_DATA_R = 0x00;
    // GPIO_PORTC_DATA_R = 0x00;

}

void LCD4bits_Cmd( unsigned char command ){
    LCD_Write4bits(command & 0xF, 0x00);
    LCD_Write4bits(command << 4, 0x00);

    if(command < 4){
        delayMs(2);    // Wait for 2ms
    } else {
        delayUs(1);    // Wait for 1ms
    }
}

void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data & 0xF0  , RS);      //upper nibble first
	LCD_Write4bits(data << 4    , RS);      //then lower nibble
	delayUs(40);												//delay for LCD (MCU is faster than LCD)
}

void LCD_WriteString(INT8U * str, INT8U len) {  
  INT8U i;
  for (i = 0; i < len; i++) {
    LCD4bits_Data(str[i]);
  }
}

void delayMs(int n)
{  
	volatile int i,j;             //volatile is important for variables incremented in code
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)         //delay for 1 msec
		{}
}

void delayUs(int n)             
{
	volatile int i,j;							//volatile is important for variables incremented in code
	for(i=0;i<n;i++)
		for(j=0;j<3;j++)            //delay for 1 micro second
		{}
}

/****************************** End Of Module *******************************/

void delay(volatile int time) {
  while (time > 0) {
    time--;
  }
}


// IR = Instruction register
// DR = Data register

// The board uses a 4-bit interface to MPU


// USE RS=0 to send comands, like clear display
// USE RS=1 to send data, like characters to display








