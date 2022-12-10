#include "vga.h"
#include "io_ports.h"
#include "types.h"

uint16_t vga_item_entry(uint8_t ch, VGA_COLOR_TYPE fore_color,
                        VGA_COLOR_TYPE back_color) {
  uint16_t ax = 0;
  uint8_t ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void vga_set_cursor_pos(uint8_t x, uint8_t y) {
  // The screen is 80 characters wide...
  uint16_t cursorLocation = y * VGA_WIDTH + x;
  outb(0x3D4, 14);
  outb(0x3D5, cursorLocation >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, cursorLocation);
}

void vga_disable_cursor() {
  outb(0x3D4, 10);
  outb(0x3D5, 32);
}
