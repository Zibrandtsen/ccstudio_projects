/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: status led.h
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
* 100408  KHA    Module created.
*
*****************************************************************************/

#ifndef _LED_H
  #define _LED_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


void led_init(void);

void green_led_task(void *pvParameters);
void yellow_led_task(void *pvParameters);
void red_led_task(void *pvParameters);

/****************************** End Of Module *******************************/
#endif

