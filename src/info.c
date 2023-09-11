#include "types.h"
#include "info.h"

void __cpuid(uint32_t type, uint32_t *eax, uint32_t *ebx, uint32_t *ecx,
             uint32_t *edx)
{
    asm volatile("cpuid"
                 : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                 : "0"(type)); // put the type into eax
}

int cpuid_info(int print)
{
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

    if (print)
    {
        printf("Brand: %s\n", brand);
    }

    if (strstr(brand, "QEMU") != NULL)
        return BRAND_QEMU;

    return BRAND_VBOX;
}