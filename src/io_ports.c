#include "io_ports.h"

/**
 * read a byte from given port number
 */
uint8_t inportb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/**
 * write a given byte to given port number
 */
void outportb(uint16_t port, uint8_t val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

/**
 * read 2 bytes(short) from given port number
 */
uint16_t inports(uint16_t port) {
  uint16_t rv;
  asm volatile("inw %1, %0" : "=a"(rv) : "dN"(port));
  return rv;
}

/**
 * write given 2 bytes(short) to given port number
 */
void outports(uint16_t port, uint16_t data) {
  asm volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

/**
 * read 4 bytes(long) from given port number
 */
uint32_t inportl(uint16_t port) {
  uint32_t rv;
  asm volatile("inl %%dx, %%eax" : "=a"(rv) : "dN"(port));
  return rv;
}

/**
 * write given 4 bytes(long) to given port number
 */
void outportl(uint16_t port, uint32_t data) {
  asm volatile("outl %%eax, %%dx" : : "dN"(port), "a"(data));
}
