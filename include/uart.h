
#include <pico/stdlib.h>

static void btn_fxn(uint gpio, uint32_t eventMask);
static void print_task(void *arg);
static void receive_task(void *arg);
