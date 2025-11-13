#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 15

void buzzer_task(void *arg) {
    (void)arg;

    //Initialize the buzzer
    init_buzzer();
    printf("Initializing buzzer\n");

    while(1){
        buzzer_play_tone (440, 500);
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}

