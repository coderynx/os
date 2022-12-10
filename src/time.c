#include "time.h"
#include "io_ports.h"
#include "types.h"

// Read a byte from the specified CMOS register
uint8_t read_cmos(uint8_t reg) {
  // Select the register to read from
  outportb(CMOS_ADDRESS, reg);

  // Read the value from the register
  return inportb(CMOS_DATA);
}

// Get the current time and date from the CMOS
void get_time(uint8_t *seconds, uint8_t *minutes, uint8_t *hours,
              uint8_t *day_of_week, uint8_t *day_of_month, uint8_t *month,
              uint8_t *year) {
  // Check if CMOS registers are using binary or BCD format
  uint8_t status = read_cmos(RTC_HOURS);
  uint8_t binary = (status & CMOS_BINARY) ? 1 : 0;

  // Read the seconds register
  *seconds = read_cmos(RTC_SECONDS);
  if (!binary)
    *seconds = (*seconds & 0x0F) + ((*seconds / 16) * 10);

  // Read the minutes register
  *minutes = read_cmos(RTC_MINUTES);
  if (!binary)
    *minutes = (*minutes & 0x0F) + ((*minutes / 16) * 10);

  // Read the hours register
  *hours = read_cmos(RTC_HOURS);
  if (!binary)
    *hours = (*hours & 0x0F) + ((*hours / 16) * 10);

  // Read the day of the week register
  *day_of_week = read_cmos(RTC_DAY_OF_WEEK);

  // Read the day of the month register
  *day_of_month = read_cmos(RTC_DAY_OF_MONTH);
  if (!binary)
    *day_of_month = (*day_of_month & 0x0F) + ((*day_of_month / 16) * 10);

  // Read the month register
  *month = read_cmos(RTC_MONTH);
  if (!binary)
    *month = (*month & 0x0F) + ((*month / 16) * 10);

  // Read the year register
  *year = read_cmos(RTC_YEAR);
  if (!binary)
    *year = (*year & 0x0F) + ((*year / 16) * 10);
}
