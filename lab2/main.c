#include <stdint.h>
#include "tm4c123gh6pm.h"   // Board specific header
#include "emp_type.h"       // Define types
#include "systick.h"        // Timer

/**
 * main.c
 */

#define TIM_1_SEC     200
extern int ticks;


int taskA(void){
    INT16U var1 = 0b11111111;
    var1 &=  ~(0x60);   //bit 5 and 6
    return 0;
}

int taskB(void){
    INT16U varb;
    INT16U var2 = 0xFFFF; // X –any number you enter
    varb = ~0b011111100000 | 0b001111000000;    // Create 0b1111 1011 1101 1111
    var2 &= varb;   // And them to create zeros
    return 0;
}

int taskC(void){
    INT16U var_task_C = 0xAAAA;
    INT16U mask = 0x0001;

    int dummy;
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;        // enable the GPIO port that is used for the on-board LEDs and switches
    dummy = SYSCTL_RCGC2_R;                     // dummy read to insert a few cycles after enabling the peripheral
    GPIO_PORTF_DIR_R = 0x0E;                    // set the direction as output for LED pins on PortF (PF1 - PF3)
    GPIO_PORTF_DEN_R = 0x1E;                    // enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_PUR_R = 0x10;                    // enable internal pull-up resistor for switch (PF4)

    while(1){
        if(GPIO_PORTF_DATA_R & 0x10){           // switch not pressed
            GPIO_PORTF_DATA_R &= ~(0x02);       // red LED off
            GPIO_PORTF_DATA_R |= 0x04;          // blue LED on
        }
        else{                                   // switch pressed
            if(var_task_C & mask)               // is the masked bit a 1?       var_task_C= 1010101010101010
            {
                GPIO_PORTF_DATA_R |= 0x02;      // red LED on
                GPIO_PORTF_DATA_R &= ~(0x04);   // blue LED off
            }
            mask=mask<<1;
            while(!(GPIO_PORTF_DATA_R & 0x10))
            {
            }    // wait here until the switch is released
        }
    }

    return 0;
}

int taskD(void){
    int alive_timer = TIM_1_SEC;
    init_systick();

    INT16U var_task_C = 0xAAAA;
    INT16U mask = 0x0001;

    int dummy;
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;        // enable the GPIO port that is used for the on-board LEDs and switches
    dummy = SYSCTL_RCGC2_R;                     // dummy read to insert a few cycles after enabling the peripheral
    GPIO_PORTF_DIR_R = 0x0E;                    // set the direction as output for LED pins on PortF (PF1 - PF3)
    GPIO_PORTF_DEN_R = 0x1E;                    // enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_PUR_R = 0x10;                    // enable internal pull-up resistor for switch (PF4)

    while(1){
        while (!ticks); // Wait for ticks = 1 (while(ticks==0))

        // The following will be executed every 5mS
        ticks--;

        if( ! --alive_timer ){
            alive_timer        = TIM_1_SEC;

            if(var_task_C & mask)               // is the masked bit a 1?       var_task_C= 1010101010101010
            {
                GPIO_PORTF_DATA_R |= 0x02;      // red LED on
                GPIO_PORTF_DATA_R &= ~(0x04);   // blue LED off
            }
            else {
                GPIO_PORTF_DATA_R &= ~(0x02);       // red LED off
                GPIO_PORTF_DATA_R |= 0x04;          // blue LED on
            }

        mask=mask<<1;

        }
    }

    return 0;
}


int main(void)
{

    // taskA();
    // taskB();
    // taskC();
    taskD();



    return 0;
}
