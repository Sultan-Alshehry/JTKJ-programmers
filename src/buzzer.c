#include "buzzer.h"
#include <stdio.h>

#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "tkjhat/sdk.h"

QueueHandle_t queue;

int melody[] = {1318, 1174, 1318, 1174, 1318, 880, 988, 1046, 988, 880};
float durations[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25};

void play_sound(sound music){
    xQueueSend(queue, &music, portMAX_DELAY);
}

void buzzer_task(void *arg) {
    (void)arg;

    //Initialize the buzzer
    init_buzzer();
    printf("Initializing buzzer\n");
    queue = xQueueCreate(5,sizeof(sound));
    

    while(1){

        sound nextSound;
        if (xQueueReceive(queue, &nextSound, portMAX_DELAY) == pdPASS) {
            switch (nextSound) {
                case MESSAGE_RECEIVED:
                    for (int i=0 ; i<10; i++){
                        buzzer_play_tone (melody[i], 50);
                        vTaskDelay(pdMS_TO_TICKS(durations[i]));
                    }
                    break;
                case MESSAGE_SENT:

                    break;
                default:
                    break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

