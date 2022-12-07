#ifndef LOGGER_H
#define LOGGER_H

#define LOG_INFO(message) kern_log(LOG_LEVEL_INFO, message)
#define LOG_DEBUG(message) kern_log(LOG_LEVEL_DEBUG, message)
#define LOG_WARN(message) kern_log(LOG_LEVEL_WARN, message)
#define LOG_ERROR(message) kern_log(LOG_LEVEL_ERROR, message)
#define LOG_FATAL(message) kern_log(LOG_LEVEL_FATAL, message)

typedef enum
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} kern_log_level_t;

void kern_log(kern_log_level_t, const char *);

#endif