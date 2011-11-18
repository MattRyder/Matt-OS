
#ifndef GDT_H
#define GDT_H

#include "common.h"
/* A single GDT Entry data structure */
struct gdt_entry 
{
  u16int limit_low;
  u16int base_low;
  u8int base_mid;
  u8int access;
  u8int granularity;
  u8int base_high;
} __attribute__((packed));

struct gdt_ptr 
{
  u16int limit;
  u32int base;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;
typedef struct gdt_ptr gdt_ptr_t;

//Prototypes:
void init_tables();

#endif