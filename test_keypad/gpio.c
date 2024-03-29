/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: gpio.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
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
#include "gpio.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_gpio(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
	int dummy;

	// Enable the GPIO port that is used for the on-board LED.
	SYSCTL_RCGC2_R  =  SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOF;
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
	dummy = SYSCTL_RCGC2_R;

	// Set the direction as output (PF1, PF2 and PF3).
	GPIO_PORTC_DIR_R = 0xF0;
	GPIO_PORTD_DIR_R = 0x4C;
	GPIO_PORTF_DIR_R = 0x0E;

	// Enable the GPIO pins for digital function (PF0, PF1, PF2, PF3, PF4).
	GPIO_PORTC_DEN_R = 0xF0;
	GPIO_PORTD_DEN_R = 0x4C;
	GPIO_PORTF_DEN_R = 0x1F;

	// Enable internal pull-up (PF0 and PF4).
	GPIO_PORTF_PUR_R = 0x11;
}

void init_keypad(void) {
	// KeyB D: PA2	- X3
	// KeyB E: PA3	- X2
	// KeyB F: PA4	- X1
	// KeyB G: PE0  - Y4
	// KeyB H: PE1  - Y3
	// KeyB J: PE2  - Y2
	// KeyB K: PE3  - Y1

	// int dummy;	

	// // Enable clock for port A and E
	// // SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOE;
	// SYSCTL_RCGC2_R |= 0x01 | 0x10;

	// // Do a dummy read to insert a few cycles after enabling the peripheral.
	// dummy = SYSCTL_RCGC2_R;

	// // Configure PortA as digital input
	// GPIO_PORTA_DEN_R |= 0x1C;
	// GPIO_PORTA_DIR_R &= ~0x1C;
	// // GPIO_PORTA_PUR_R |= 0x1C;
	// GPIO_PORTA_PDR_R |= 0x1C;
	
	// // Configure PortE as digital output
	// GPIO_PORTE_DEN_R |= 0x0F;
	// GPIO_PORTE_DIR_R |= 0x0F;
	// // GPIO_PORTE_PUR_R |= 0x0F;
	int dummy;

	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOE;
	SYSCTL_RCGCGPIO_R |= 0x11; // Enable clock for port A and E
	while((SYSCTL_RCGCGPIO_R & 0x11) == 0);

	dummy = SYSCTL_RCGC2_R;

	GPIO_PORTA_CR_R |= 0x1C;
	GPIO_PORTA_DIR_R |= 0x1C;	// Set as output
	GPIO_PORTA_DEN_R |= 0x1C;

	GPIO_PORTE_CR_R |= 0x0F;
	GPIO_PORTE_DIR_R &= ~0x0F;	// Set as input
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_PDR_R |= 0x0F;

}

/****************************** End Of Module *******************************/
