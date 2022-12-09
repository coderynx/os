#ifndef LOGGER_H
#define LOGGER_H

#ifdef DEBUG
#define LOG_DEBUG(format, ...) kern_log(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#endif

#define LOG_INFO(format, ...) kern_log(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) kern_log(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) kern_log(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) kern_log(LOG_LEVEL_FATAL, format, ##__VA_ARGS__)

typedef enum {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL
} kern_log_level_t;

void kern_log(kern_log_level_t, const char *format, ...);

#endif