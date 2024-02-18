/********** Header ************/
/********** Include files ************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

/********** Defines ************/
#define TIM_1_SEC 200
#define DEBOUNCE_TIMEOUT 50
#define DOUBLE_CLICK_TIMEOUT 150
#define LONG_PRESS_TIMEOUT 400

/********** Constants ************/
/********** Variabels ************/
extern int ticks;
int counter = 0;
int LED_dir = 1;
long release = 0;
long press = 0;
int counter2 = 0;


/********** Functions ************/

void delay(int ms){
	int cycles = 16000 * ms;	// magic number
	while(cycles){
		cycles--;
	}
}

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

void buttonHandler(void){
	counter2 = 1;
	if ((release - press) > DEBOUNCE_TIMEOUT) {
		GPIO_PORTF_IM_R &= 0x10;
		ticks = 0;
		counter2 = 3;	

		while(DOUBLE_CLICK_TIMEOUT > ticks){
			if(isButtonPressed()){
				LED_dir = !LED_dir;
				counter2 = 6;
			}
		}
		updateCounter(LED_dir);

	} 
	// else if ((release - press) > LONG_PRESS_TIMEOUT) {
	// 	//set to auto
	// 	counter2=5;
	// }

	GPIO_PORTF_IM_R = 0x10;

}

void buttonISR(void){
	if(isButtonPressed()){	// When SW1 is pressed
		press = ticks;
		counter2 = 2;
	}
	else {					// When SW1 is released
		release = ticks;
		counter2 = 4;
		buttonHandler();
	}


	// if(isButtonPressed()){
	// 	setLED(counter);
	// 	updateCounter(LED_dir);
	// 	delay(50);	// Debounce protection
	// }

    GPIO_PORTF_ICR_R = 0x10;  // Clear the interrupt flag for PF4
}

void setup(){
	init_systick();

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

updateCounter(int direction){
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
	// __enable_irq();  // Enable global interrupts

	int alive_timer = TIM_1_SEC;
	
	
	while(1){
		setLED(counter2);
		// if(!(GPIO_PORTF_DATA_R & 0x10)){	// When SW1 is pressed
		// 	rgbLed(counter);
		// 	counter++;
			
		// 	if (counter > 7){
		// 		counter = 0;
		// 	}
		// 	// delay(20);

		// } 

		// if(isButtonPressed()){	// When SW1 is pressed
		// 	setLED(counter);
		// 	updateCounter(0);

		// 	while(--alive_timer) {
		// 		while( !ticks );    // Wait for ticks = 1 (while(ticks==0))

		// 		// The following will be executed every 5mS
		// 		ticks--;
		// 	}
		// 	alive_timer        = TIM_1_SEC;
		// }
	}

	return 0;
}

			
