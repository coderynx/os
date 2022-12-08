#include "kernel.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "io_ports.h"
#include "keyboard.h"
#include "logger.h"
#include "memory.h"
#include "names.h"
#include "string.h"
#include "terminal.h"
#include "timer.h"

typedef struct {
  char *name;
  char *surname;
  char *username;
} user_t;

void kmain() {
  gdt_init();
  idt_init();
  timer_init();

  console_init(COLOR_WHITE, COLOR_BLACK);

  LOG_INFO("Initializing coderynxOS...");
  LOG_INFO("Boot successful");

  user_t *user = (user_t *)malloc(sizeof(user_t));
  user->username = "johndoe";
  user->name = "John";
  user->surname = "Doe";

  char str[100];
  sprintf(str, "Welcome %s %s (%s)", user->name, user->surname, user->username);

  LOG_INFO(str);

  free(user);

  keyboard_init();
  term_start();
}
