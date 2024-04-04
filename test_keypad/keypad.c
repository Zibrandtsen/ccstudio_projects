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
// #include "lcd.h"
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

INT8U key_col_pushed(){     // Y
    return ( !(GPIO_PORTE_DATA_R & 0x0F) );
}

INT8U key_row_pushed(){     // X
    return ( !( GPIO_PORTA_DATA_R & 0x1C ) );
}

char keypad_scan() {
    volatile int row, col;
    char key = '\0';

    // Iterate over rows
    for (col = 0; col < COLS; col++) {
        // Activate one row at a time
        GPIO_PORTA_DATA_R = (1 << (col + 2));
        // delay(1600);

        // Iterate over columns
        for (row = 0; row < ROWS; row++) {
            // Check if any key is pressed
            // uint32_t x = GPIO_PORTE_DATA_R & 0x0F;
            if ( (GPIO_PORTE_DATA_R & 0x0F) == (1 << (row)) ) {
                // GPIO_PORTF_DATA_R ^= 0x08;  // TODO remove
                // Key pressed, return corresponding character
                key = keys[row][col];
                return key;
            }
        }
    }
    // GPIO_PORTF_DATA_R ^= 0x08;  // TODO remove
    // No key pressed
    return '\0';
}

char keypad_task(){
    static char pressed_key;

    // Continuously scan for key presses
    pressed_key = keypad_scan();
    // delay(160000);
    
    // Process the pressed key
    switch (pressed_key) {
        case '1':   // * or 0
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '2':   // 7 or 8
            // GPIO_PORTF_DATA_R |= 0x04;
            break;
        case '3':   // 
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '4':   // #
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '5':   // 9
            GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '6':   //
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '7':   //
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '8':   //
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '9':   //
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '*':   //
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '0':   // (5+8)
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '#':   //
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
        case '\0':
            GPIO_PORTF_DATA_R &= 0x00;
            // GPIO_PORTF_DATA_R ^= 0x02;
            break;
        default:
            // GPIO_PORTF_DATA_R |= 0x08;
            break;
    }
    delay(160000);
    return pressed_key;
}


/****************************** End Of Module *******************************/



