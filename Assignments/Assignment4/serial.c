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
// INT8U recived_bytes[6] = {};
// INT8U recived_bytes_len = sizeof(recived_bytes);


/*****************************   Functions   *******************************/
// transmit funcs
void uart0_transmit_byte(INT8U byte) {
    while ( !uart0_tx_rdy() );  // Wait for TX buffer to be empty
    uart0_putc(byte);        // Transmit character
}

void uart0_transmit_string(char *str, INT8U len) {
	INT8U i;
  	for (i = 0; i < len; i++) {
		uart0_transmit_byte(str[i]);
  	}
}

// receove funcs
INT8U uart0_receive_byte() {
  while ( !uart0_rx_rdy() );  // Wait for RX buffer to be full
  return uart0_getc();        // Read character
}

INT8U * uart0_read_message(INT8U* buffer, INT8U length) {
    INT8U i;
    for(i = 0; i < length; i++) {
        buffer[i] = uart0_receive_byte();
    }
    return buffer;
}




void uart0_task(){
    if(uart0_rx_rdy()){

        switch (uart0_receive_byte())
        {
        case '1':
            out_LCD('1');
            // delayMs(30);
            // uart0_read_message(recived_bytes, recived_bytes_len);
            // INT8U i;
            // for(i = 0; i < recived_bytes_len; i++) {
            //     out_LCD(recived_bytes[i]);
            // }
            break;
        case '2':
            // send message
            break;
        
        default:
            break;
        }
    }
}

/****************************** End Of Module *******************************/












