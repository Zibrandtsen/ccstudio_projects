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

enum KEYPAD_states
{
  KEYPAD_WAIT,
  KEYPAD_PRESSED,
};


/*****************************    Defines    *******************************/
#define ROWS 4
#define COLS 3

/*****************************   Constants   *******************************/
// Define the keypad layout
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/
void delay (volatile unsigned int delay) {
    volatile unsigned int i, j;
    for (i=0; i<delay; i++);
        for (j=0; j<12; j++);
}

INT8U sw1_pushed()
{
    return( !( GPIO_PORTF_DATA_R & 0x10 ) );
}

INT8U key_row_pushed(){     // Y
    return ( !(GPIO_PORTE_DATA_R & 0x0F) );
}

INT8U key_col_pushed(){     // X
    return ( !( GPIO_PORTA_DATA_R & 0x1C ) );
}

char keypad_scan() {
    int row, col;

    // Iterate over rows
    for (row = 0; row < ROWS; row++) {
        // Activate one row at a time
        GPIO_PORTA_DATA_R = ~(1 << (row + 2));
        delay(1600);

        // Iterate over columns
        for (col = 0; col < COLS; col++) {
            // Check if any key is pressed
            if ( (GPIO_PORTE_DATA_R & 0x0F) == (1 << col)) {
                // Key pressed, return corresponding character
                GPIO_PORTF_DATA_R ^= 0x08;  // TODO remove
                return keys[row][col];
            }
        }
    }
    // No key pressed
    return '\0';
}

void keypad_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data){
    static char pressed_key;

    switch (my_state)
    {
    case SW1_WAIT:
        if(sw1_pushed())                 //if SW1 pushed
        {
            set_state(SW1_PRESSED);         //change state
        }
        break;
    
    case SW1_PRESSED:
        if(!sw1_pushed())                //if button released, change state and signal
        {
            GPIO_PORTF_DATA_R ^= 0x04;
            set_state(SW1_WAIT);
            preset_sem(SEM_SW1, 1);         //signal semaphore
        } 
        break;
    default:
        break;
    }

    // Continuously scan for key presses
    pressed_key = keypad_scan();
    delay(160000);
    // Process the pressed key
    switch (pressed_key) {
        case '1':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '2':
            GPIO_PORTF_DATA_R ^= 0x02;
            break;
        case '3':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '4':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '5':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '6':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '7':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '8':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '9':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '*':
            // GPIO_PORTF_DATA_R ^= 0x02;
            // break;
        case '0':
            GPIO_PORTF_DATA_R ^= 0x08;
            // break;
        case '#':
            // GPIO_PORTF_DATA_R &= ~0x02;
            break;
        case '\0':
            // GPIO_PORTF_DATA_R &= ~0x08;
            GPIO_PORTF_DATA_R ^= 0x04;
            break;
        default:
            //GPIO_PORTF_DATA_R &= ~0x02;
            break;
    }


}


/****************************** End Of Module *******************************/



