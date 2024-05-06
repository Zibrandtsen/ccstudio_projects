#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick_frt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "status_led.h"
//#include "led.h"
//#include "tmodel.h"
#include "file.h"

//#include "uart.h"
//#include "keypad.h"
#include "queue.h"
#include "semphr.h"
#include "lcd.h"
#include "emp_type.h"
#include "gpio.h"


#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3


#define QUEUE_LEN   128

QueueHandle_t xQueue_lcd;
SemaphoreHandle_t xSemaphore_lcd;

static void setupHardware(void){
    init_systick();
    status_led_init();
    //init_adc();
    init_gpio();

    xQueue_lcd = xQueueCreate( QUEUE_LEN, sizeof(INT8U) );
    xSemaphore_lcd = xSemaphoreCreateMutex();
}

int main() {
    setupHardware();
    xTaskCreate(status_led_task, "Status_led", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
    xTaskCreate(lcd_task, "LCD", USERTASK_STACK_SIZE, NULL, MED_PRIO, NULL);

    vTaskStartScheduler();
    return 0;
}
