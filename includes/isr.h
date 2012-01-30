#ifndef ISR_H
#define ISR_H

#include "common.h"
#include "monitor.h"
#include "string.h"

typedef struct registers
{
  u32int ds;
  u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32int int_no, err_code;				//Interrupt number and an error code (if one available)
  u32int eip, cs, eflags, useresp, ss;				//Pushed by the CPU automatically
} registers_t;

void isr_handler(registers_t registers);

unsigned char* isr_message[] =
{
    "DIVISION BY ZERO",
    "DEBUG EXCEPTION",
    "NON MASKABLE INTERRUPT EXCEPTION",
    "BREAKPOINT EXCEPTION",
    "INTO DETECTED OVERFLOW EXCEPTION",
    "OUT OF BOUNDS EXCEPTION",
    "INVALID OPCODE EXCEPTION",
    "NO COPROCESSOR EXCEPTION",
    "DOUBLE FAULT EXCEPTION",
    "COPROCESSOR SEGMENT OVERRUN EXCEPTION",
    "BAD TSS EXCEPTION",
    "SEGMENT NOT PRESENT EXCEPTION",
    "STACK FAULT EXCEPTION",
    "GENERAL PROTECTION FAULT EXCEPTION",
    "PAGE FAULT EXCEPTION",
    "UNKNOWN INTERRUPT EXCEPTION",
    "COPROCESSOR FAULT EXCEPTION",
    "ALIGNMENT CHECK EXCEPTION",        //On 486+ machines
    "MACHINE CHECK EXCEPTION",          //On Pentium/586+ machines
    "UNDEFINED / RESERVED EXCEPTION"
};

#endif
