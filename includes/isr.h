#ifndef ISR_H
#define ISR_H

#include "common.h"
#include "monitor.h"
#include "string.h"

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct registers
{
  u32int ds;
  u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32int int_no, err_code;				//Interrupt number and an error code (if one available)
  u32int eip, cs, eflags, useresp, ss;	//Pushed by the CPU automatically
} registers_t;

void isr_handler(registers_t registers);
void irq_handler(registers_t registers);

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8int irq_no, isr_t handler);

char* isr_message[] =
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
