#include "terminal.h"
#include "console.h"
#include "io_ports.h"
#include "logger.h"
#include "names.h"
#include "string.h"
#include "vga.h"

#define BRAND_QEMU 1
#define BRAND_VBOX 2

void __cpuid(uint32 type, uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx) {
  asm volatile("cpuid"
               : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
               : "0"(type)); // put the type into eax
}

int cpuid_info(int print) {
  uint32 brand[12];
  uint32 eax, ebx, ecx, edx;
  uint32 type;

  memset(brand, 0, sizeof(brand));
  __cpuid(0x80000002, (uint32 *)brand + 0x0, (uint32 *)brand + 0x1,
          (uint32 *)brand + 0x2, (uint32 *)brand + 0x3);
  __cpuid(0x80000003, (uint32 *)brand + 0x4, (uint32 *)brand + 0x5,
          (uint32 *)brand + 0x6, (uint32 *)brand + 0x7);
  __cpuid(0x80000004, (uint32 *)brand + 0x8, (uint32 *)brand + 0x9,
          (uint32 *)brand + 0xa, (uint32 *)brand + 0xb);

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

BOOL is_echo(char *b) {
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
  printf("\n");
  const char *shell = OS_NAME ":" OS_VERSION "# ";
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
      printf("Commands: help, cpuid, echo, shutdown, testlog\n");
    } else if (is_echo(buffer)) {
      printf("%s\n", buffer + 5);
    } else if (strcmp(buffer, "shutdown") == 0) {
      shutdown();
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