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
#include "lcd.h"
#include "glob_def.h"
#include "tmodel.h"

enum SW1_states
{
  SW1_WAIT,
  SW1_PRESSED,
};


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/


/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/
INT8U button_pushed()
{
    // return( (!(GPIO_PORTA_DATA_R & 0x10)) && (!(GPIO_PORTE_DATA_R & 0x08)) );
    return( !(GPIO_PORTF_DATA_R & 0x10) );
}

void keypad_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data){
    switch (my_state)
    {
    case SW1_WAIT:
        if(button_pushed())                 //if SW1 pushed
        {
            set_state(SW1_PRESSED);         //change state
        }
        break;
    
    case SW1_PRESSED:
        if(!button_pushed())                //if button released, change state and signal
        {
            GPIO_PORTF_DATA_R ^= 0x02;
            set_state(SW1_WAIT);
            preset_sem(SEM_SW1, 1);         //signal semaphore
        } 
        break;
    default:
        break;
    }
}


/****************************** End Of Module *******************************/




