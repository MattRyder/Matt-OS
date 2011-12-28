#include "../includes/descriptor_tables.h"

extern void gdt_flush(u32int);
extern void idt_flush(u32int);

static void init_gdt();
static void init_idt();

static void gdt_set_gate(s32int, u32int, u32int, u8int, u8int);
static void idt_set_gate(u8int, u32int, u16int, u8int); // (idt_num, idt_base, idt_selector, idt_flags)

gdt_ptr_t	gdt_ptr;
idt_ptr_t	idt_ptr;

gdt_entry_t 	gdt_entries[5];
idt_entry_t	idt_entries[256];

//Initializes the GDT and IDT tables
void init_tables()
{
  init_gdt();
  init_idt();
}

static void init_gdt()
{
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 5)-1;
  gdt_ptr.base  = (u32int)&gdt_entries;
  
  gdt_set_gate(0, 0, 0, 0, 0); 			// NULL SEGMENT
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	// RING0 CODE SEGMENT [kernel]
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	// RING0 DATA SEGMENT [kernel]
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	// RING3 CODE SEGMENT [usermode]
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	// RING3 DATA SEGMENT [usermode]
  
  gdt_flush((u32int)&gdt_ptr);
  
}

static void init_idt()
{
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = (u32int)&idt_entries; //give it idt_entries[0];
  
  memset(&idt_entries, 0, sizeof(idt_entry_t)*256);
  
  idt_set_gate(0, (u32int)isr0, 0x08, 0x8E);
  idt_set_gate(1, (u32int)isr1, 0x08, 0x8E);
  idt_set_gate(2, (u32int)isr2, 0x08, 0x8E);
  idt_set_gate(3, (u32int)isr3, 0x08, 0x8E);
  idt_set_gate(4, (u32int)isr4, 0x08, 0x8E);
  idt_set_gate(5, (u32int)isr5, 0x08, 0x8E);
  idt_set_gate(6, (u32int)isr6, 0x08, 0x8E);
  idt_set_gate(7, (u32int)isr7, 0x08, 0x8E);
  idt_set_gate(8, (u32int)isr8, 0x08, 0x8E);
  idt_set_gate(9, (u32int)isr9, 0x08, 0x8E);
  idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
  idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
  idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
  idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
  idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
  idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
  idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
  idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
  idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
  idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
  idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
  idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
  idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
  idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
  idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
  idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
  idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
  idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
  idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
  idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
  idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
  idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);
  
  //All ISRs set up! load the IDT!
  idt_flush((u32int)&idt_ptr);
}

static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int granularity)
{
  gdt_entries[num].base_low  = (base & 0xFFFF);
  gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;
  
  gdt_entries[num].limit_low = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0x0F; 
  
  gdt_entries[num].granularity |= granularity & 0xF0;
  gdt_entries[num].access = access;
}

static void idt_set_gate(u8int num, u32int base, u16int selector, u8int flags)
{
  idt_entries[num].base_low  = base & 0xFFFF;
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;
  
  idt_entries[num].selector = selector;
  idt_entries[num].permanull = 0;
  
  idt_entries[num].flags = flags;
}
