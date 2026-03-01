#include "power.h"

#include "io_ports.h"

void shutdown() {
    outports(0x604, 0x2000);
    outports(0xB004, 0x2000);
    outports(0x4004, 0x3400);

    // If power-off doesn't happen immediately, stop executing.
    for (;;) {
        asm volatile("hlt");
    }
}

static void i8042_wait_input_empty(void) {
    for (uint32_t i = 0; i < 100000; i++) {
        if ((inb(0x64) & 0x02) == 0)
            return;
    }
}

void reset() {
    i8042_wait_input_empty();
    outb(0x64, 0xFE);

    outb(0xCF9, 0x06);
    outb(0xCF9, 0x0E);

    // If reset doesn't happen immediately, stop executing.
    for (;;) {
        asm volatile("hlt");
    }
}
