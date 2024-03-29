#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "gpio.h"
#include "keypad.h"

/**
 * main.c
 */
int main(void)
{
	init_gpio();
	init_keypad();
	char key;
	while(1){
		key = keypad_task();
	}
	return 0;

}
