#ifndef IO_PORTS_H
#define IO_PORTS_H

#include "types.h"

/**
 * read a byte from given port number
 */
uint8_t inb(uint16_t port);

/**
 * write a given byte to given port number
 */
void outb(uint16_t port, uint8_t val);

/**
 * read 2 bytes(short) from given port number
 */
uint16_t inports(uint16_t port);

/**
 * write given 2(short) bytes to given port number
 */
void outports(uint16_t port, uint16_t data);

/**
 * read 4 bytes(long) from given port number
 */
uint32_t inportl(uint16_t port);

/**
 * write given 4 bytes(long) to given port number
 */
void outportl(uint16_t port, uint32_t data);

#endif
