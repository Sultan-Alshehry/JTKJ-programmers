#include <stdio.h>

#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#include "tkjhat/sdk.h"

void buzzer_task(void *arg) {
    (void)arg;

    //Initialize the buzzer
    init_buzzer();
    printf("Initializing buzzer\n");

    while(1){
        buzzer_play_tone (440, 50);
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}

