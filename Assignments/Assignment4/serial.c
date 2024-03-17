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
#include "queue.h"

/*****************************    Defines    *******************************/
#define SERIAL_SET_CLOCK '1'
#define SERIAL_GET_CLOCK '2'

#define SERIAL_ERROR_INVALID_HOUR 1
#define SERIAL_ERROR_INVALID_MIN  2
#define SERIAL_ERROR_INVALID_SEC  3

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/
// transmit funcs
void uart0_transmit_byte(INT8U byte) {
    while ( !uart0_tx_rdy() );  // Wait for TX buffer to be empty
    uart0_putc(byte);           // Transmit character
}

void uart0_transmit_string(char *str, INT8U len) {
	INT8U i;
  	for (i = 0; i < len; i++) {
		uart0_transmit_byte(str[i]);
  	}
}

void uart0_transmit_queue(INT8U id, INT8U len) {
	INT8U i;
  	for (i = 0; i < len; i++) {
        uart0_transmit_byte(queue_get(id));
  	}
}

// receive funcs
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

// time queue funcs
INT8U queue_get_time_unit(INT8U id){
    INT8U  time_unit  = (queue_get(id) - '0') * 10;
    return time_unit += (queue_get(id) - '0');
}

void queue_put_time_unit(INT8U id, INT8U time_unit){
        queue_put(id, (time_unit / 10) + '0');
        queue_put(id, (time_unit % 10) + '0');
}

// task
void uart0_task(){
    INT8U hour, min, sec;
    INT8U error = 1;

    if(uart0_rx_rdy())
    {
        switch (uart0_receive_byte()) {
        case SERIAL_SET_CLOCK:   

            // Put UART0 RX into queue (expect 6 bytes)
            if (wait ( MUTEX_UART0 )){
                INT8U i;
                for (i = 0; i < 6; i++) {
                    queue_put(Q_UART_RX, uart0_receive_byte());
                }
                signal( MUTEX_UART0 );
            }

            // Get time from queue
            hour = queue_get_time_unit(Q_UART_RX);
            min  = queue_get_time_unit(Q_UART_RX);
            sec  = queue_get_time_unit(Q_UART_RX);
            
            // Check if time is valid
            if (0 <= hour && hour <= 23) {
                if (0 <= min && min <= 59) {
                    if (0 <= sec && sec <= 59) {
                        error = 0;
                    }
                }
            }

            if (error) {
                if (wait( MUTEX_UART0 )) {
                    uart0_transmit_string("Error: Invalied time", 20);
                    signal( MUTEX_UART0 );
                }
            }
            
            // Update time on LCD
            if (wait ( MUTEX_LCD_DISPLAY )) {     // MUTEX_SYSTEM_RTC
                put_msg_state( SSM_RTC_HOUR, hour );
                put_msg_state( SSM_RTC_MIN, min );
                put_msg_state( SSM_RTC_SEC, sec );

                signal( MUTEX_LCD_DISPLAY );
            }
            break;

        case SERIAL_GET_CLOCK:

            // Get time from RTC
            if (wait( MUTEX_SYSTEM_RTC )){   // wait for RTC mutex
                hour = get_msg_state( SSM_RTC_HOUR );
                min  = get_msg_state( SSM_RTC_MIN  );
                sec  = get_msg_state( SSM_RTC_SEC  );
                signal( MUTEX_SYSTEM_RTC );  // release RTC mutex
            }

            // Put time into UART0 TX queue
            queue_put_time_unit(Q_UART_TX, hour);
            queue_put_time_unit(Q_UART_TX, min);
            queue_put_time_unit(Q_UART_TX, sec);

            // Transmit time
            if (wait ( MUTEX_UART0 )) {  // wait for UART0 TX mutex
                uart0_transmit_byte('2');
                uart0_transmit_queue(Q_UART_TX, 6);
                signal( MUTEX_UART0 );   // release UART0 TX mutex
            }

            break;
        
        default:
            break;
        }
    }
}


/****************************** End Of Module *******************************/












