#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"

/**
 * main.c
 */


int taskA(void){
    INT16U var1 = 0b11111111;
    var1 &=  ~(0x60);   //bit 5 and 6
    return 0;
}


int main(void)
{

    //taskA();
    INT16U varb;
    INT16U var2 = 0xFFFF; // X –any number you enter
    varb = ~0b011111100000 | 0b001111000000;    // Create
    var2 &= varb;
    //TODO check:)



    return 0;
}
