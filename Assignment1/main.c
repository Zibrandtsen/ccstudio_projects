/********** Header ************/
/********** Include files ************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

/********** Defines ************/
#define TIM_1_SEC 200
#define DEBOUNCE_TIMEOUT 1
#define DOUBLE_CLICK_TIMEOUT 10
#define LONG_PRESS_TIMEOUT 200

/********** Constants ************/
/********** Variabels ************/
extern int ticks;
int counter = 0;
int LED_dir = 1;
long press_duration = 0;


/********** Functions ************/

void setLED(int colour){
	GPIO_PORTF_DATA_R &= 0b0001;	// Turn off the LED at places 1, 2 and 3

	switch (colour){
		case 1:
			GPIO_PORTF_DATA_R |= (1<<3);	// Green
			break;
		case 2:
			GPIO_PORTF_DATA_R |= (1<<2);	// Blue
			break;
		case 3:
			GPIO_PORTF_DATA_R |= (1<<2)|(1<<3);	// Cyan
			break;
		case 4:
			GPIO_PORTF_DATA_R |= (1<<1);	// Red
			break;
		case 5:
			GPIO_PORTF_DATA_R |= (1<<1)|(1<<3);	// Yellow
			break;
		case 6:
			GPIO_PORTF_DATA_R |= (1<<1)|(1<<2);	// Magenta (Lilla)
			break;
		case 7:
			GPIO_PORTF_DATA_R |= (1<<1)|(1<<2)|(1<<3); // White
			break;
		default:
			break;
		}
}

int isButtonPressed(){
	return ~GPIO_PORTF_DATA_R & 0x10;
}

void updateCounter(int direction);

void buttonHandler(void){
	ticks = 0;
	GPIO_PORTF_IM_R &= ~0x10;	// Disable interrupt for PF4

	if (press_duration >= LONG_PRESS_TIMEOUT){
		setLED(0);
	} else if(press_duration >= DEBOUNCE_TIMEOUT){
		// while(DEBOUNCE_TIMEOUT >= ticks){
		// 	if(isButtonPressed()){
		// 		LED_dir = !LED_dir;
		// 	}
		// 	while(isButtonPressed()){}
		// }
		updateCounter(LED_dir);
		setLED(counter);
	}


	// }
	GPIO_PORTF_ICR_R |= 0x10;
	GPIO_PORTF_IM_R |= 0x10;	// Enable interrupt for PF4

}

void buttonISR(void){
	if(isButtonPressed()){	// When SW1 is pressed
		ticks = 0;
	} else {					// When SW1 is released
		press_duration = ticks;
		buttonHandler();
	}
    GPIO_PORTF_ICR_R |= 0x10;  // Clear the interrupt flag for PF4
}

void setup(){
	int dummy;
	
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; 	// enable the GPIO port that is used for the on-board LEDs and switches
	dummy = SYSCTL_RCGC2_R;					// dummy read to insert a few cycles after enabling the peripheral

	// GPIO_LOCK_KEY = 0x4C4F434B;				// Unlock the GPIO_CR register
	// GPIO_PORTF_LOCK_R = 0x4C4F434B;
	// GPIO_PORTF_AHB_LOCK_R = GPIO_LOCK_KEY;

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  // Enable clock to Port F

	// Set LED as output
	GPIO_PORTF_DIR_R = 0x0E;

	// Enable the GPIO pins for digital function (PF0 - PF4).
	GPIO_PORTF_DEN_R = 0x1F;

	// Enable internal pull-up (PF0 and PF4)
    GPIO_PORTF_PUR_R = 0x11;

	// Interrupts??
	NVIC_EN0_R |= 1 << 30;  // Enable interrupt for Port F (bit 30 in EN0 corresponds to Port F)

	GPIO_PORTF_IS_R &= ~0x10;  // PF4 is edge-sensitive (not level-sensitive)
	GPIO_PORTF_IBE_R |= 0x10; // PF4 is not both edges (just falling edge)
	// GPIO_PORTF_IEV_R &= 0x10; // PF4 rising edge event
	GPIO_PORTF_ICR_R = 0x10;   // Clear any prior interrupt on PF4
	GPIO_PORTF_IM_R = 0x10;   // Enable interrupt on PF4

}

void updateCounter(int direction){
	if(direction)
		counter++;
	else
		counter--;
	if(0 > counter)
		counter = 7;
	counter = counter % 8;
}

int main(void) {
	setup();
	init_systick();

	int alive_timer = TIM_1_SEC;
	
	
	// while(1){
	// 	setLED(counter);
	// }

	return 0;
}

			
