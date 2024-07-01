#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include <stdint.h>
#include "SPI_init.h"

void SPI1_init(void)
{
    /* Enable clock to SPI1, GPIOD and GPIOF */

    SYSCTL_RCGCSSI_R |= (1<<1);   /*set clock enabling bit for SPI1 */
    SYSCTL_RCGCGPIO_R |= (1<<3); /* enable clock to GPIOD for SPI1 */
    SYSCTL_RCGCGPIO_R |= (1<<5); /* enable clock to GPIOF for slave select */

    /*Initialize PD3 and PD0 for SPI1 alternate function*/

    GPIO_PORTD_AMSEL_R &= ~0x0F;      /* disable analog functionality RD0 and RD3 */
    GPIO_PORTD_DEN_R |= 0x0F;         /* Set RD0 and RD3 as digital pin */
    GPIO_PORTD_AFSEL_R |= 0x0F;       /* enable alternate function of RD0 and RD3*/
    GPIO_PORTD_PCTL_R &= ~0x0000FFFF; /* assign RD0 and RD3 pins to SPI1 */
    GPIO_PORTD_PCTL_R |= 0x00002222;  /* assign RD0 and RD3 pins to SPI1 (Number 2 to enable PD0-PD3 SSI1 - clck - Fss - Rx and Tx) page 651 */

    /* Initialize PF2 as a digital output as a slave select pin */

    //GPIO_PORTF_DEN_R |= (1<<2);         /* set PF2 pin digital */
    //GPIO_PORTF_DIR_R |= (1<<2);         /* set PF2 pin output */
    //GPIO_PORTF_DATA_R |= (1<<2);        /* keep SS idle high */

    /* Select SPI1 as a Master, POL = 0, PHA = 0, clock = 4 MHz, 8 bit data */

    SSI1_CR1_R = 0;          /* disable SPI1 and configure it as a Master */
    SSI1_CC_R = 0;           /* Enable System clock Option */
    SSI1_CPSR_R = 4;         /* Select prescaler value of 4 .i.e 16MHz/4 = 4MHz */
    SSI1_CR0_R = 0x00007;     /* 4MHz SPI1 clock, SPI mode, 8 bit data */
    SSI1_CR1_R |= 2;         /* enable SPI1 */

    // Enable Pull up resistor for button (PF4)
    GPIO_PORTF_PUR_R = 0X10;
    //Set the direction as output (PF4)
    GPIO_PORTF_DIR_R = 0x0E;
    // Enable the GPIO pins for digital function (PF4)
    GPIO_PORTF_DEN_R = 0x1E;
}
