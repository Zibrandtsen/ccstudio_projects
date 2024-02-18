/********** Header ************/
/********** Include files ************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

/********** Defines ************/
#define TIM_1_SEC	 200

/********** Constants ************/
/********** Variabels ************/
extern int ticks;


/********** Functions ************/

void delay(int ms){
	int cycles = 16000 * ms;	// magic number
	while(cycles){
		cycles--;
	}
}

void rgbLed(int colour){
	GPIO_PORTF_DATA_R &= 0b0001;	// Turn off the LED at places 1, 2 and 3

	switch (colour){
		case 1:
			GPIO_PORTF_DATA_R |= (1<<3);	// Turn on the green LED
			break;
		case 2:
			GPIO_PORTF_DATA_R |= (1<<2);
			break;
		case 3:
			GPIO_PORTF_DATA_R |= (1<<2)|(1<<3);
			break;
		case 4:
			GPIO_PORTF_DATA_R |= (1<<1);
			break;
		case 5:
			GPIO_PORTF_DATA_R |= (1<<1)|(1<<3);
			break;
		case 6:
			GPIO_PORTF_DATA_R |= (1<<1)|(1<<2);
			break;
		case 7:
			GPIO_PORTF_DATA_R |= (1<<1)|(1<<2)|(1<<3);
			break;
		default:
			break;
		}
}


/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program and is called when the program starts.
 * It initializes the program and executes the main logic.
 *
 * @args:
 * @return:
 */
int main(void) {
	int counter = 0;

	int alive_timer = TIM_1_SEC;
	init_systick();

	#pragma region Init
	int dummy;
	
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; 	// enable the GPIO port that is used for the on-board LEDs and switches
	dummy = SYSCTL_RCGC2_R;					// dummy read to insert a few cycles after enabling the peripheral

	// GPIO_LOCK_KEY = 0x4C4F434B;				// Unlock the GPIO_CR register
	GPIO_PORTF_LOCK_R = 0x4C4F434B;

	// Set LED as output
	GPIO_PORTF_DIR_R = 0x0E;

	// Enable the GPIO pins for digital function (PF0 - PF4).
	GPIO_PORTF_DEN_R = 0x1F;

	// Enable internal pull-up (PF0 and PF4)
    GPIO_PORTF_PUR_R = 0x11;
	#pragma endregion
	
	while(1){
		// if(!(GPIO_PORTF_DATA_R & 0x10)){	// When SW1 is pressed
		// 	rgbLed(counter);
		// 	counter++;
			
		// 	if (counter > 7){
		// 		counter = 0;
		// 	}
		// 	// delay(20);

		// } 
		if(!(GPIO_PORTF_DATA_R & 0x10)){	// When SW1 is pressed
			
			
			while( !ticks );    // Wait for ticks = 1 (while(ticks==0))

			// The following will be executed every 5mS
			ticks--;

			if( ! --alive_timer ) {
				alive_timer        = TIM_1_SEC;

				counter++;
				if (counter > 7){
					counter = 0;
				}
                rgbLed(counter);
				
			}
		}
	}

	return 0;
}

			
