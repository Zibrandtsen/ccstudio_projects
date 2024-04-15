/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "emp_type.h"
//#include "glob_def.h"
//#include "binary.h"
#include "status_led.h"
#include "adc.h"


/*****************************    Defines    *******************************/
#define PF0		0		// Bit 0

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void led_init(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	
*****************************************************************************/
{
  INT8S dummy;

  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOF;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as output (PF1, PF2 and PF3).
  GPIO_PORTF_DIR_R = 0x0E;
  // Set the direction as output (PD6).
  GPIO_PORTD_DIR_R = 0x40;

  // Enable the GPIO pins for digital function (PF0, PF1, PF2, PF3, PF4).
  GPIO_PORTF_DEN_R = 0x1F;
  // Enable the GPIO pins for digital function (PD6).
  GPIO_PORTD_DEN_R = 0x40;

  // Enable internal pull-up (PF0 and PF4).
  GPIO_PORTF_PUR_R = 0x11;
}


void green_led_task(void *pvParameters)
{
	status_led_init();

	while(1)
	{
		// Toggle status led
    GPIO_PORTF_DATA_R ^= 0x08;
		vTaskDelay(3000 / portTICK_RATE_MS); // wait 3000 ms.
	}
}

void yellow_led_task(void *pvParameters)
{
	status_led_init();

	while(1)
	{
		// Toggle status led
    GPIO_PORTF_DATA_R ^= 0x04;
		vTaskDelay(2000 / portTICK_RATE_MS); // wait 2000 ms.
	}
}

void red_led_task(void *pvParameters)
{
	status_led_init();
    INT16U adc_value;
    portTickType delay;

	while(1)
	{
        adc_value = get_adc();
        delay = 1000 - adc_value / 5;
		// Toggle status led
        GPIO_PORTF_DATA_R ^= 0x02;
		vTaskDelay( delay / portTICK_RATE_MS); // wait  ms.
	}
}



/****************************** End Of Module *******************************/




