#include "uart.h"
#include "buzzer.h"
#include "interface.h"

#include <string.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include "tkjhat/sdk.h"
#include "state.h"

#define DEFAULT_STACK_SIZE 2048

#define INPUT_BUFFER_SIZE 256

void send_message() {
  printf("%s", g_state.currentMessage);
  strcpy(g_state.messageHistory[g_state.messageHistorySize].message, g_state.currentMessage);
  g_state.messageHistory[g_state.messageHistorySize].sender = 0;
  g_state.messageHistory[g_state.messageHistorySize].message_size = strlen(g_state.currentMessage);
  g_state.messageHistorySize++;
  g_state.currentMessage[0] = 0;
  g_state.currentMessageSize = 0;
  play_sound(MESSAGE_RECEIVED);
}

void receive_task(void *arg) {
  (void)arg;
  char line[INPUT_BUFFER_SIZE];
  size_t index = 0;

  while (1) {
    absolute_time_t next = delayed_by_us(get_absolute_time(), 500);//Wait 500 us
    int read = stdio_get_until(line,INPUT_BUFFER_SIZE,next);
    if (read == PICO_ERROR_TIMEOUT){
        vTaskDelay(pdMS_TO_TICKS(100)); // Wait for new message
    }
    else {
        line[read] = '\0'; //Last character is 0
        printf("__[RX] \"%s\"\n__", line);
        strcpy(g_state.messageHistory[g_state.messageHistorySize].message, line);
         g_state.messageHistory[g_state.messageHistorySize].sender = 1;
         g_state.messageHistory[g_state.messageHistorySize].message_size = strlen(line);
         g_state.messageHistorySize++;
         update_interface();
         play_sound(MESSAGE_RECEIVED);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
  }
}
