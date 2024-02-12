/********** Header ************/
/********** Include files ************/
#include <stdint.h>
#include "tm4c123gh6pm.h"

/********** Defines ************/
/********** Constants ************/
/********** Variabels ************/


/********** Functions ************/

int main(void) {
	/********** 
	 * Input: 
	 * Output:
	 * Function:  
	 *************/

	int dummy;
	
	int counter;

	// Enable the GPIO port that is used for the on-board LED and switches.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; //TODO - what is dis???

	dummy = SYSCTL_RCGC2_R;

	// Set LED as output
	GPIO_PORTF_DIR_R = 0x0E;

	// Enable the GPIO pins for digital function (PF0 - PF4).
	GPIO_PORTF_DEN_R = 0x1F;

	// Enable internal pull-up (PF0 and PF4)
    GPIO_PORTF_PUR_R = 0x11;


	counter = 0;
	while(1){
		if(GPIO_PORTF_DATA_R & (1<<4)){	// If SW1 is pressed ??
			GPIO_PORTF_DATA_R &= (0<<1); // Turn off LED at place 1

		} else {
			// Turn off the LED at places 1, 2 and 3
			GPIO_PORTF_DATA_R |= (1<<1);
			GPIO_PORTF_DATA_R &= ~(1<<2);
			GPIO_PORTF_DATA_R &= ~(1<<3);
		}
	}

	return 0;
}



		// Turn on the LED.
			// GPIO_PORTF_DATA_R &= ~(1<<3);
			// if(counter == 8){
			// 	counter = 0;
			// } else if (counter == 1) {
			// 	GPIO_PORTF_DATA_R = (1<<3);
			// } else if (counter == 2) {
			// 	GPIO_PORTF_DATA_R = (1<<2);
			// } else if (counter == 3) {
			// 	GPIO_PORTF_DATA_R = (1<<2)|(1<<3);
			// } else if (counter == 4) {
			// 	GPIO_PORTF_DATA_R = (1<<1);
			// } else if (counter == 5) {
			// 	GPIO_PORTF_DATA_R = (1<<1)|(1<<3);
			// } else if (counter == 6) {
			// 	GPIO_PORTF_DATA_R = (1<<1)|(1<<2);
			// } else if (counter == 7) {
			// 	GPIO_PORTF_DATA_R = (1<<1)|(1<<2)|(1<<3);
			// }
			
