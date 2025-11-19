typedef enum {
    MESSAGE_RECEIVED,
    MESSAGE_SENT,
    JEEEEEE,
    MUSIC,
    WOOOOOHOOOOOO
} Sound;

void buzzer_task(void *arg);
void play_sound(Sound sound);