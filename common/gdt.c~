/* GLOBAL DESCRIPTOR TABLES
 * Who's accessing your segments? 
 */

#include "../includes/gdt.h"

extern void gdt_flush(u32int);

static void init_gdt();
static void gdt_set_gate(s32int, u32int, u32int, u8int, u8int);

gdt_ptr_t	gdt_ptr;
gdt_entry_t 	gdt_entries[5];

//Initializes the GDT and IDT tables
void init_tables()
{
  
  init_gdt();
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

static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int granularity)
{
  gdt_entries[num].base_low  = (base & 0xFFFF);
  gdt_entries[num].base_mid  = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;
  
  gdt_entries[num].limit_low = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0x0F; 
  
  gdt_entries[num].granularity |= granularity & 0x0F;
  gdt_entries[num].access = access;
}

