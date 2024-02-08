#include <stdint.h>
#include "tm4c123gh6pm.h"

/**
 * main.c
 */
int main(void) {
	int dummy;
	
	// Enable the GPIO port that is used for the on-board LED and switches.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; //TODO - what is dis???

	dummy = SYSCTL_RCGC2_R;

	// Set LED as output
	GPIO_PORTF_DIR_R = 0x0E;

	// Enable the GPIO pins for digital function (PF0 - PF4).
	GPIO_PORTF_DEN_R = 0x1F;

	// Enable internal pull-up (PF0 and PF4)
    GPIO_PORTF_PUR_R = 0x11;

	while(1){
		if(GPIO_PORTF_DATA_R & (1<<4)){
			// Turn on the LED.
			GPIO_PORTF_DATA_R &= ~(1<<3);
		} else {
			// Turn off the LED.
			GPIO_PORTF_DATA_R |= (1<<3);
		}
	}

	return 0;
}
