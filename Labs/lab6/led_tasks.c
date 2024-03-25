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
#include "emp_type.h"
#include "led_tasks.h"

#include "rtcs.h"
#include "button.h"


/*****************************    Defines    *******************************/
#define EMP_RED_LED    0x02
#define EMP_YELLOW_LED 0x04
#define EMP_GREEN_LED  0x08

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/
void button_task(){
    if (button_pushed()) {
        SSM_SW1_PUSHED = 1;
    }
    
}

void sw1_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data){
    switch ( my_state ) {
        case SSM_SW1_PUSHED:
    }
}

void red_led_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data){
    wait( 200 * 5 );    // Wait for 200 approx. 1 sec.
    GPIO_PORTF_DATA_R ^= EMP_RED_LED;
}



/****************************** End Of Module *******************************/




