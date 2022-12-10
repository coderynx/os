#include "time.h"
#include "cmos.h"
#include "io_ports.h"
#include "types.h"

// Get the current time and date from the CMOS
time_t get_time(void) {
  // Declare time_t struct
  time_t time;

  // Check if CMOS registers are using binary or BCD format
  uint8_t status = read_cmos(RTC_HOURS);
  uint8_t binary = (status & CMOS_BINARY) ? 1 : 0;

  // Read the seconds register
  time.seconds = read_cmos(RTC_SECONDS);
  if (!binary)
    time.seconds = (time.seconds & 0x0F) + ((time.seconds / 16) * 10);

  // Read the minutes register
  time.minutes = read_cmos(RTC_MINUTES);
  if (!binary)
    time.minutes = (time.minutes & 0x0F) + ((time.minutes / 16) * 10);

  // Read the hours register
  time.hours = read_cmos(RTC_HOURS);
  if (!binary)
    time.hours = (time.hours & 0x0F) + ((time.hours / 16) * 10);

  // Read the day of the week register
  time.day_of_week = read_cmos(RTC_DAY_OF_WEEK);

  // Read the day of the month register
  time.day_of_month = read_cmos(RTC_DAY_OF_MONTH);
  if (!binary)
    time.day_of_month =
        (time.day_of_month & 0x0F) + ((time.day_of_month / 16) * 10);

  // Read the month register
  time.month = read_cmos(RTC_MONTH);
  if (!binary)
    time.month = (time.month & 0x0F) + ((time.month / 16) * 10);

  // Read the year register
  time.year = read_cmos(RTC_YEAR);
  if (!binary)
    time.year = (time.year & 0x0F) + ((time.year / 16) * 10);

  return time;
}
