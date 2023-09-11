#include "info.h"
#include "power.h"

void shutdown()
{
    int brand = cpuid_info(0);
    if (brand == BRAND_QEMU)
        outports(0x604, 0x2000);
    else
        outports(0x4004, 0x3400);
}

void reset()
{
    int brand = cpuid_info(0);
    if (brand == BRAND_QEMU)
        outb(0x64, 0xFE);
}