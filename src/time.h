#ifndef TIME_H
#define TIME_H

#include "types.h"

typedef struct {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day_of_week;
  uint8_t day_of_month;
  uint8_t month;
  uint8_t year;
} time_t;

time_t get_time(void);

#endif