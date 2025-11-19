#include <FreeRTOS.h>
#include <semphr.h>

#include "state.h"

State state;

static SemaphoreHandle_t state_mutex = NULL;

void state_init() {
    //state_mutex = xSemaphoreCreateMutex();
    state.status = MAIN_MENU;
    state.messageHistorySize = 0;
}


void set_status(Status new_status) {
    //xSemaphoreTake(state_mutex, portMAX_DELAY);
    state.status = new_status;
    //xSemaphoreGive(state_mutex);
}

Status get_status() {
    Status current_status;
    //xSemaphoreTake(state_mutex, portMAX_DELAY);
    current_status = state.status;
    //xSemaphoreGive(state_mutex);
    return current_status;
}
