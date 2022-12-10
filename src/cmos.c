#include "cmos.h"
#include "io_ports.h"
#include "types.h"

// Read a byte from the specified CMOS register
uint8_t read_cmos(uint8_t reg) {
  // Select the register to read from
  outportb(CMOS_ADDRESS, reg);

  // Read the value from the register
  return inportb(CMOS_DATA);
}
