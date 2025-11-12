#include<stdio.h>
#include <FreeRTOS.h>
#include <task.h>

#include "tkjhat/sdk.h"
#include "interface.h"

#define DEFAULT_I2C_SDA_PIN   12
#define DEFAULT_I2C_SCL_PIN   13

void display_task(void *arg) {
    (void)arg;

    init_display();
    printf("Initializing display\n");

    while(1) {
        
        clear_display();
        char buf[5]; //Store a number of maximum 5 figures 
        sprintf(buf, "Hi!");
        write_text(buf);
        vTaskDelay(pdMS_TO_TICKS(4000));
    }

}
