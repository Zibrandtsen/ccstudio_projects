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
    signal( MUTEX_UART0 );

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

    }
    return( 0 );
}
