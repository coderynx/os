#include "logger.h"
#include "console.h"
#include "string.h"
#include "vga.h"

void kern_log(kern_log_level_t log_level, const char *format, ...) {
  va_list args;
  va_start(args, format);

  switch (log_level) {
  case LOG_LEVEL_DEBUG:
    set_fore_color(COLOR_BRIGHT_BLUE);
    printf("[DEBUG]");
    break;
  case LOG_LEVEL_INFO:
    set_fore_color(COLOR_GREEN);
    printf("[INFO]");
    break;
  case LOG_LEVEL_WARN:
    set_fore_color(COLOR_YELLOW);
    printf("[WARN]");
    break;
  case LOG_LEVEL_ERROR:
    set_fore_color(COLOR_RED);
    printf("[ERROR]");
    break;
  case LOG_LEVEL_FATAL:
    set_back_color(COLOR_RED);
    printf("[FATAL]");
    set_back_color(COLOR_BLACK);
    break;
  }

  set_fore_color(COLOR_WHITE);
  printf(": ");
  vprintf(format, args);

  printf("\n");
  va_end(args);
}
