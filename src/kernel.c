#include "kernel.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "io_ports.h"
#include "keyboard.h"
#include "logger.h"
#include "memory.h"
#include "mouse.h"
#include "names.h"
#include "string.h"
#include "terminal.h"
#include "timer.h"

void kmain(void)
{
  gdt_init();
  idt_init();
  timer_init();

  console_init(COLOR_WHITE, COLOR_BLACK);

  LOG_INFO("Initializing coderynxOS...");
  LOG_INFO("Boot successful");

  keyboard_init();

  term_start();
}