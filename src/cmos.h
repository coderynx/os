#ifndef CMOS_H
#define CMOS_H

#include "types.h"

// CMOS registers
#define CMOS_ADDRESS 0x0070
#define CMOS_DATA 0x0071

// CMOS registers for time and date
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04
#define RTC_DAY_OF_WEEK 0x06
#define RTC_DAY_OF_MONTH 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09

// Flag to indicate if CMOS registers use binary or BCD format
#define CMOS_BINARY 0x04

uint8_t read_cmos(uint8_t);

#endif