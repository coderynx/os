#include "logger.h"
#include "console.h"
#include "string.h"

void kern_log(kern_log_level_t log_level, const char * in_string) {
    switch (log_level)
    {
    case LOG_LEVEL_DEBUG:
        set_fore_color(COLOR_BRIGHT_BLUE);
        printf("[DEBUG]");
        set_fore_color(COLOR_WHITE);
        printf(": %s\n", in_string);
        break;
    case LOG_LEVEL_INFO:
        set_fore_color(COLOR_GREEN);
        printf("[INFO]");
        set_fore_color(COLOR_WHITE);
        printf(": %s\n", in_string);
        break;
    case LOG_LEVEL_WARN:
        set_fore_color(COLOR_YELLOW);
        printf("[WARN]");
        set_fore_color(COLOR_WHITE);
        printf(": %s\n", in_string);
        break;
    case LOG_LEVEL_ERROR:
        set_fore_color(COLOR_RED);
        printf("[ERROR]");
        set_fore_color(COLOR_WHITE);
        printf(": %s\n", in_string);
        break;
    case LOG_LEVEL_FATAL:
        set_back_color(COLOR_RED);
        printf("[FATAL]");
        set_back_color(COLOR_BLACK);
        printf(": %s\n", in_string);
        break;
    }
}