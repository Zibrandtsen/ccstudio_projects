/********** Header ************/
/********** Include files ************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"
#include "emp_type.h"

/********** Defines ************/
#define TIM_1_SEC 200


/********** Constants ************/
/********** Variabels ************/
volatile uint32_t ui32Loop;
extern int ticks;
INT8U correct_sequence[] = {1, 2, 2, 1, 2}; 

int state_counter = 0;
int incorrect_sequence = 0; 

/********** Functions ************/
void bla(input){
    state_counter++;

    switch (state_counter){
    case 1:
        if (input != 1){
            incorrect_sequence = 1;
        }
        break;
    case 2:
        if (input != 2){
            incorrect_sequence = 1;
        }
        break;
    case 3:
        if (input != 2){
            incorrect_sequence = 1;
        }
        break;
    case 4:
        if (input != 1){
            incorrect_sequence = 1;
        }
        break;
    case 5:
        if (input != 2){
            incorrect_sequence = 1;
        }
        break;
    
    default:
        break;
    }
}
void setup(){
    int dummy;
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;        // enable the GPIO port that is used for the on-board LEDs and switches
    dummy = SYSCTL_RCGC2_R;                     // dummy read to insert a few cycles after enabling the peripheral
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
    GPIO_PORTF_DIR_R = 0x0E;                    // set the direction as output for LED pins on PortF (PF1 - PF3)
    GPIO_PORTF_DEN_R = 0x1F;                    // enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_PUR_R = 0x11;                    // enable internal pull-up resistor for switch (PF4)
}

void delay(int ms){
	int cycles = 16000 * ms;	// magic number
	while(cycles){
		cycles--;
	}
}
void click_detected(){
    GPIO_PORTF_DATA_R &= ~(0x08);   // Turn off green
    for(ui32Loop = 0; ui32Loop < 240000; ui32Loop++){}; // Wait 200ms
    GPIO_PORTF_DATA_R |= 0x02;    // Turn on red
}

int main(void) {
    // int alive_timer = TIM_1_SEC;
    // init_systick();

    setup();
    GPIO_PORTF_DATA_R |= 0x02;  // Turn on red

    while(1){
        
        if(~GPIO_PORTF_DATA_R & 0x10) {
            click_detected();
            bla(1);
            while(!(GPIO_PORTF_DATA_R & 0x10)){}  // wait here until the switch is released
        }
        else if (~GPIO_PORTF_DATA_R & 0x01){
            click_detected();
            bla(2);
            while(!(GPIO_PORTF_DATA_R & 0x01)){}  // wait here until the switch is released
        }


        if(state_counter == 5){
            if(incorrect_sequence == 0){
                GPIO_PORTF_DATA_R &= ~(0x02);  // Turn off all LEDs
                GPIO_PORTF_DATA_R |= 0x08;  // Turn on green
            }
            else{
                GPIO_PORTF_DATA_R &= 0x00;  // Turn off all LEDs
                GPIO_PORTF_DATA_R |= (1<<1)|(1<<2)|(1<<3);
                delay(30);
                GPIO_PORTF_DATA_R &= 0x02; // Turn on red

            }
            incorrect_sequence = 0;
            state_counter = -1;
        }



        // while( !ticks );    // Wait for ticks = 1 (while(ticks==0))

        // // The following will be executed every 5mS
        // ticks--;

        // if( ! --alive_timer ) {
        //   alive_timer        = TIM_1_SEC;
        //   GPIO_PORTF_DATA_R ^= 0x04;
        // }
    }
    return 0;
}
