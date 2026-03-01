#include "types.h"
#include "info.h"

#include "console.h"
#include "string.h"

void __cpuid(uint32_t type, uint32_t *eax, uint32_t *ebx, uint32_t *ecx,
             uint32_t *edx)
{
    asm volatile("cpuid"
                 : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                 : "0"(type)); // put the type into eax
}

int cpuid_info(int print)
{
    char brand[49];
    uint32_t eax, ebx, ecx, edx;

    memset(brand, 0, sizeof(brand));

    __cpuid(0x80000002, &eax, &ebx, &ecx, &edx);
    ((uint32_t*)brand)[0] = eax;
    ((uint32_t*)brand)[1] = ebx;
    ((uint32_t*)brand)[2] = ecx;
    ((uint32_t*)brand)[3] = edx;

    __cpuid(0x80000003, &eax, &ebx, &ecx, &edx);
    ((uint32_t*)brand)[4] = eax;
    ((uint32_t*)brand)[5] = ebx;
    ((uint32_t*)brand)[6] = ecx;
    ((uint32_t*)brand)[7] = edx;

    __cpuid(0x80000004, &eax, &ebx, &ecx, &edx);
    ((uint32_t*)brand)[8]  = eax;
    ((uint32_t*)brand)[9]  = ebx;
    ((uint32_t*)brand)[10] = ecx;
    ((uint32_t*)brand)[11] = edx;

    if (print)
    {
        printf("Brand: %s\n", brand);
    }

    if (strstr(brand, "QEMU") != NULL)
        return BRAND_QEMU;

    return BRAND_VBOX;
}