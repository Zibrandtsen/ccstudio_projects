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
#include "tmodel.h"

/*****************************    Defines    *******************************/
#define SERIAL_SET_CLOCK '1'
#define SERIAL_GET_CLOCK '2'

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
    INT8U hour, min, sec;
    if(uart0_rx_rdy()){

        switch (uart0_receive_byte())
        {
        case SERIAL_SET_CLOCK:       // SET CLOCK
            // TODO: Check if values hour, min and sec are valid

            // read values for hour
            hour =  (uart0_receive_byte() - '0') * 10;
            hour += (uart0_receive_byte() - '0');
            put_msg_state( SSM_RTC_HOUR, hour );        // send a message with the hour value

            // read values for min
            min =  (uart0_receive_byte() - '0') * 10;
            min += (uart0_receive_byte() - '0');
            put_msg_state( SSM_RTC_MIN, min );          // send a message with the hour value

            // read values for sec
            sec =  (uart0_receive_byte() - '0') * 10;
            sec += (uart0_receive_byte() - '0');
            put_msg_state( SSM_RTC_SEC, sec );          // send a message with the hour value

            break;
        case SERIAL_GET_CLOCK:       // GET CLOCK
            uart0_transmit_byte('2');

            hour = get_msg_state( SSM_RTC_HOUR );
            uart0_transmit_byte( (hour / 10) + '0' );
            uart0_transmit_byte( (hour % 10) + '0' );

            min = get_msg_state( SSM_RTC_MIN );
            uart0_transmit_byte( (min / 10) + '0' );
            uart0_transmit_byte( (min % 10) + '0' );

            sec = get_msg_state( SSM_RTC_SEC );
            uart0_transmit_byte( (sec / 10) + '0' );
            uart0_transmit_byte( (sec % 10) + '0' );

            break;
        
        default:
            break;
        }
    }
}

/****************************** End Of Module *******************************/












