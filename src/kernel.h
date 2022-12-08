#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

// symbols from linker.ld for section addresses
extern uint8_t __kernel_section_start;
extern uint8_t __kernel_section_end;
extern uint8_t __kernel_text_section_start;
extern uint8_t __kernel_text_section_end;
extern uint8_t __kernel_data_section_start;
extern uint8_t __kernel_data_section_end;
extern uint8_t __kernel_rodata_section_start;
extern uint8_t __kernel_rodata_section_end;
extern uint8_t __kernel_bss_section_start;
extern uint8_t __kernel_bss_section_end;

#endif
