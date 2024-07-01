#include "tm4c123gh6pm.h"
#include "SPI_Write.h"
#include "emp_type.h"
#include <stdint.h>


void SPI1_Write(unsigned char data)
{
    while((SSI1_SR_R & 2) == 0); /* wait untill Tx FIFO is not full */
    SSI1_DR_R = data;            /* transmit byte over SSI1Tx line */
    while(SSI1_SR_R & 0x10);     /* wait until transmit complete */
}
