#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "gpio.h"
#include "systick.h"
#include "swtimers.h"
#include "tmodel.h"
#include "messages.h"
#include "systick.h"
#include "sem.h"
#include "button.h"
#include "rtc.h"
#include "lcd.h"

#include "uart0.h"

extern volatile INT16S ticks;
INT16S alive_timer = MILLISEC(500);

void delayMs(int n)
{  
	volatile int i,j;             //volatile is important for variables incremented in code
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)         //delay for 1 msec
		{}
}

int main(void)
/*****************************************************************************
*   Input    : NONE
*   Output   : Returns 0
*   Function : Init hardware and then loop forever
******************************************************************************/
{
    init_systick();
    init_gpio();
    uart0_init(19200, 8, 1, 0);

    signal( MUTEX_SYSTEM_RTC );
    signal( MUTEX_LCD_DISPLAY );
    signal( SEM_RTC_UPDATED );

    // INT8U recived_bytes;
    clr_LCD();

    // Loop forever.
    while(1)
    {
        // System part of the super loop.
        // ------------------------------
        while( !ticks );

        // The following will be executed every 5mS
        ticks--;

        if( ! --alive_timer )
        {
            alive_timer = MILLISEC( 500 );
            GPIO_PORTD_DATA_R ^= 0x40;
        }

        // Protected operating system mode
        swt_ctrl();

        // Application mode
        button_task( TASK_BUTTON );
        rtc_task( TASK_RTC );       // Real time clock
        display_rtc_task( TASK_RTC_DISPLAY );
        ajust_rtc_task( TASK_RTC_ADJUST );
        lcd_task( TASK_LCD );
        uart0_task();

////
        // ------------------------------
        // w//le(uart0_rx_rdy()) {
        //     // // Echo
        //     // INT8U aahh = uart0_receive_byte();
        //     // uart0_transmit_byte(aahh);

        //     i++;
            
        //     charArray[i] = uart0_getc();
            
        //     // char *stringArray = charArray;
    
        // }
        // if (i > 1){
        //     // uart0_transmit_string(charArray, 8);
        //     uart0_transmit_byte('r');
        //     i = 0;         
        // }
        // ------------------------------

        
        // recived_bytes = uart0_receive_byte();
        // if('r' == recived_bytes){
        //     GPIO_PORTF_DATA_R |= 0x04;
        //     out_LCD(recived_bytes);
        // } else if('c' == recived_bytes) {
        //     clr_LCD();
        // }else {
        //     GPIO_PORTF_DATA_R &= ~0x04;
        // }

        // ---
        // read first byte

        


        // // update recived_bytes
        // uart0_read_message(recived_bytes, recived_bytes_len);

        // char recived_bytes_str[8];
        // wr_str_LCD(strcpy(recived_bytes_str, (char*)recived_bytes));



    }
    return( 0 );
}
