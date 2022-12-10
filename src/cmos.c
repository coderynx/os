#include "cmos.h"
#include "io_ports.h"
#include "types.h"

// Read a byte from the CMOS
uint8_t read_cmos(uint8_t reg) {
  // Select the register to read from
  outb(CMOS_ADDRESS, reg);

  // Read the value from the register
  return inb(CMOS_DATA);
}
