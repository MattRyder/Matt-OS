
#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#include "common.h"
#include "string.h"

/* A single GDT Entry data structure */
struct gdt_entry
{
   u16int limit_low;           // The lower 16 bits of the limit.
   u16int base_low;            // The lower 16 bits of the base.
   u8int  base_middle;         // The next 8 bits of the base.
   u8int  access;              // Access flags, determine what ring this segment can be used in.
   u8int  granularity;
   u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct gdt_ptr
{
  u16int limit;
  u32int base;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;
typedef struct gdt_ptr gdt_ptr_t;

/* INTERRUPT DESCRIPTOR TABLES */
// A single Interrupt Descriptor Table entry
struct str_idt_entry
{
  u16int base_lo;			// Lower 16 bits of the address when int is called.
  u16int sel;			// Kernel segment selector pointing to selector in the GDT.
  u8int always0;			// Forever zero, never used.
  u8int flags;				// Types and attributes for the IDT entry. DPL etc.
  u16int base_hi;			// Upper 16 bits of the address when int is called.

} __attribute__((packed));

// A ptr to an array of IDT entries.
// Passed to LIDT in idt_flush.s
struct str_idt_ptr
{
  u16int limit;
  u32int base;				// First element [0] in the IDT entry array.
} __attribute__((packed));


//Typedef them for easier maintainability!
typedef struct str_idt_entry idt_entry_t;
typedef struct str_idt_ptr idt_ptr_t;

gdt_ptr_t	gdt_ptr;
idt_ptr_t	idt_ptr;

gdt_entry_t gdt_entries[5];
idt_entry_t	idt_entries[256];

//Prototypes:
void init_tables();

extern void gdt_flush(u32int);  //Flushes the GDT in the ASM routine - flush_tables.s
extern void idt_flush(u32int);  //Flushes the IDT in the ASM routine - flush_tables.s

//Extern for isr handlers in assembly
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif
