#include "terminal.h"
#include "console.h"
#include "io_ports.h"
#include "logger.h"
#include "mouse.h"
#include "names.h"
#include "string.h"
#include "time.h"
#include "types.h"
#include "vga.h"

#define BRAND_QEMU 1
#define BRAND_VBOX 2

void __cpuid(uint32_t type, uint32_t *eax, uint32_t *ebx, uint32_t *ecx,
             uint32_t *edx) {
  asm volatile("cpuid"
               : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
               : "0"(type)); // put the type into eax
}

int cpuid_info(int print) {
  uint32_t brand[12];
  uint32_t eax, ebx, ecx, edx;
  uint32_t type;

  memset(brand, 0, sizeof(brand));
  __cpuid(0x80000002, (uint32_t *)brand + 0x0, (uint32_t *)brand + 0x1,
          (uint32_t *)brand + 0x2, (uint32_t *)brand + 0x3);
  __cpuid(0x80000003, (uint32_t *)brand + 0x4, (uint32_t *)brand + 0x5,
          (uint32_t *)brand + 0x6, (uint32_t *)brand + 0x7);
  __cpuid(0x80000004, (uint32_t *)brand + 0x8, (uint32_t *)brand + 0x9,
          (uint32_t *)brand + 0xa, (uint32_t *)brand + 0xb);

  if (print) {
    printf("Brand: %s\n", brand);
    /*for (type = 0; type < 4; type++) {
      __cpuid(type, &eax, &ebx, &ecx, &edx);
      printf("type:0x%x, eax:0x%x, ebx:0x%x, ecx:0x%x, edx:0x%x\n", type, eax,
             ebx, ecx, edx);
    }*/
  }

  if (strstr(brand, "QEMU") != NULL)
    return BRAND_QEMU;

  return BRAND_VBOX;
}

bool_t is_echo(char *b) {
  if ((b[0] == 'e') && (b[1] == 'c') && (b[2] == 'h') && (b[3] == 'o'))
    if (b[4] == ' ' || b[4] == '\0')
      return TRUE;
  return FALSE;
}

void shutdown() {
  int brand = cpuid_info(0);
  // QEMU
  if (brand == BRAND_QEMU)
    outports(0x604, 0x2000);
  else
    // VirtualBox
    outports(0x4004, 0x3400);
}

void reset() {
  int brand = cpuid_info(0);
  // QEMU
  if (brand == BRAND_QEMU)
    outb(0x64, 0xFE);
}

char buffer[255];

void print_shell_prompt() {
  set_fore_color(COLOR_BRIGHT_GREEN);
  printf(OS_NAME);
  set_fore_color(COLOR_WHITE);
  printf(":");
  set_fore_color(COLOR_BRIGHT_BLUE);
  printf(OS_VERSION);
  set_fore_color(COLOR_WHITE);
  printf("# ");
}

void term_start() {
  const char *shell = OS_NAME ":" OS_VERSION "# ";

  time_t time = get_time();
  printf("\nStarted shell session at %d:%d:%d of %d-%d-%d\n", time.hours,
         time.minutes, time.seconds, time.day_of_month, time.month, time.year);

  while (1) {
    print_shell_prompt();
    memset(buffer, 0, sizeof(buffer));
    getstr_bound(buffer, strlen(shell));
    if (strlen(buffer) == 0)
      continue;
    if (strcmp(buffer, "cpuid") == 0) {
      cpuid_info(1);
    } else if (strcmp(buffer, "help") == 0) {
      printf(OS_NAME "@" OS_VERSION " Terminal\n");
      printf("Commands: help, cpuid, echo, reset, shutdown, time, testlog\n");
    } else if (is_echo(buffer)) {
      printf("%s\n", buffer + 5);
    } else if (strcmp(buffer, "clear") == 0) {
      console_clear(COLOR_WHITE, COLOR_BLACK);
    } else if (strcmp(buffer, "shutdown") == 0) {
      shutdown();
    } else if (strcmp(buffer, "reset") == 0) {
      reset();
    } else if (strcmp(buffer, "mouse") == 0) {
      mouse_init();
    } else if (strcmp(buffer, "time") == 0) {
      time = get_time();
      printf("Time: %d:%d:%d\n", time.hours, time.minutes, time.seconds);
    } else if (strcmp(buffer, "testlog") == 0) {
      LOG_DEBUG("This is a debug");
      LOG_INFO("This is an info");
      LOG_WARN("This is a warning");
      LOG_ERROR("This is an error");
      LOG_FATAL("This is a fatal error");
    } else {
      printf("invalid command: %s\n", buffer);
    }
  }
}