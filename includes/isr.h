#ifndef ISR_H
#define ISR_H

#include "common.h"
#include "monitor.h"
#include "string.h"

typedef struct registers
{
  u32int ds;
  u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32int interrupt_num, error_code;				//Interrupt number and an error code (if one available)
  u32int eip, cs, eflags, useresp, ss;				//Pushed by the CPU automatically
} registers_t;

void isr_handler(registers_t registers);

#endif