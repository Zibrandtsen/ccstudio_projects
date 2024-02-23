/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: operation.c
*
* PROJECT....: Assignment2
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "swtimers.h"
/*****************************    Defines    *******************************/
// Operation States
// --------------
#define OS_NORWEGIAN    1
#define OS_EMERGENCY    2
#define OS_NORMAL       3

// LED defines
// -----------
#define EMP_LED_RED   	0x02	// PF1
#define EMP_LED_YELLOW  0x04	// PF2
#define EMP_LED_GREEN 	0x08	// PF3
#define EMP_LED_OFF		0x00	// All LEDs off

// -EMP-----------LILLE--        
//  RED          = CYAN
//  YELLOW       = YELLOW
//  RED + YELLOW = GREEN
//  GREEN        = MAGENTA

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void operation( INT8U event )
/*****************************************************************************
*   Input    : event from button press
*   Output   : - 
*   Function : - 
******************************************************************************/
{
    static INT8U  operation_state = OS_NORMAL;  // 0 = Idle, 1 = Single, 2 = Double, 3 = Long
    static INT8U  operation_value = 0;
    static INT16U operation_timer = 0;
    static INT8U  operation_first_run = 1;

    // If first run, set event to normal
    if (operation_first_run){
        operation_first_run = 0;
        event = BE_LONG_PUSH;
    }
    
    if (operation_timer){           // if timer is running
        if(! --operation_timer)     // decrement timer and check if now zero
            event = TE_TIMEOUT;     // then set event to timeout
    }


    if (event)  // If event is not zero
    {
        switch (operation_state) {
        case OS_NORWEGIAN:
            // Norwegian night
            switch (event){
                case TE_TIMEOUT:
                    operation_timer = TIM_1_SEC;
                    GPIO_PORTF_DATA_R ^= EMP_LED_YELLOW;
                    break;
                
                case BE_LONG_PUSH:
                    operation_state = OS_NORMAL;
                    operation_first_run = 1;
                    GPIO_PORTF_DATA_R &= EMP_LED_OFF;
                    break;
                
                default:
                    break;
            }
            // Continued
        break;
        
        case OS_EMERGENCY:
            switch (event) {
                case BE_LONG_PUSH:
                    operation_state = OS_NORMAL;
                    operation_first_run = 1;
                    GPIO_PORTF_DATA_R &= EMP_LED_OFF;
                    break;
                
                default:
                    break;
            }
            // Continued
        break;
        
        case OS_NORMAL:            
            switch (event) {
                case BE_SINGLE_PUSH:
                    operation_state = OS_NORWEGIAN;
                    operation_timer = TIM_1_SEC;
                    GPIO_PORTF_DATA_R &= EMP_LED_OFF;
                    break;
                
                case BE_DOUBBLE_PUSH:
                    operation_state = OS_EMERGENCY;
                    GPIO_PORTF_DATA_R &= EMP_LED_OFF;
                    GPIO_PORTF_DATA_R |= EMP_LED_RED;
                    break;

                default:
                    // TODO: Normal operation goes here
                    // operation_timer = TIM_500_MSEC;
                    GPIO_PORTF_DATA_R |= EMP_LED_GREEN;
                    break;
            }
            // Continued
        break;
        
            default:
                break;
        }
    }
}



/****************************** End Of Module *******************************/












