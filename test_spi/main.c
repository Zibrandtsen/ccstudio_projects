/* Example code to transmit data with SPI1 module of TM4C123 */
/* Transmits character A with a delay of one second */
#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "delay.h"
#include "SPI_Write.h"
#include "SPI_init.h"
#include "emp_type.h"


/* Main routine of code */
int main(void)
{
    unsigned char SPI_val = 'U'; // Assigns SPI VALUE


    SPI1_init();
    while(1)
        {
        if(!(GPIO_PORTF_DATA_R & 0x10)) // If button (sw2)is pressed
        {
            SPI1_Write(SPI_val); /* write a character through mosi pin */
        }
        if((SSI1_SR_R & 0x4)) // If Receive FIFO (pin 3) not full (boolean)
        {
            if(SSI1_DR_R == 'U')
            {
                GPIO_PORTF_DATA_R |= 0x08;
            }

        }

   // Delay_ms(1000);
    }
}






