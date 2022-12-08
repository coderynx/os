#ifndef CONSOLE_H
#define CONSOLE_H

#include "vga.h"

#define MAXIMUM_PAGES 16

#define SCROLL_UP 1
#define SCROLL_DOWN 2

typedef char *va_list;

#define va_start(ap, param) (ap = (va_list)&param + sizeof(param))
#define va_arg(ap, type) (*(type *)((ap += sizeof(type)) - sizeof(type)))
#define va_end(ap) (ap = (va_list)0)

void console_clear(VGA_COLOR_TYPE fore_color, VGA_COLOR_TYPE back_color);
void console_init(VGA_COLOR_TYPE fore_color, VGA_COLOR_TYPE back_color);

void set_back_color(VGA_COLOR_TYPE);
void set_fore_color(VGA_COLOR_TYPE);

void console_scroll(int line_count);
void console_putchar(char ch);

void console_ungetchar();

void console_ungetchar_bound(uint8_t n);

void console_gotoxy(uint16_t x, uint16_t y);

void console_putstr(const char *str);

void vprintf(const char *, va_list);
void printf(const char *, ...);
int sprintf(char *, const char *, ...);

void getstr(char *buffer);

void getstr_bound(char *buffer, uint8_t bound);

#endif
