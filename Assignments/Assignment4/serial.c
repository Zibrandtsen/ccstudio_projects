/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "uart0.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/



/*****************************   Functions   *******************************/
void uart0_trasmit_string(INT8U *str, INT8U len) {
	INT8U i;
  	for (i = 0; i < len; i++) {
		while ( !uart0_tx_rdy() );  // Wait for TX buffer to be empty
		uart0_putc(str[i]);        // Transmit character
  	}
}

INT8U uart0_receive_byte() {
  while ( !uart0_rx_rdy() );  // Wait for RX buffer to be full
  return uart0_getc();        // Read character
}

// Receive data
INT8U * uart0_read_message(INT8U* buffer, INT8U length) {
    INT8U i;
    for(i = 0; i < length; i++) {
        buffer[i] = uart0_receive_byte();
        delayMs(30);
    }
    return buffer;
}


/****************************** End Of Module *******************************/












