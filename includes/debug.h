
/*DEBUG.H - Methods that are used to debug the OS */

#ifndef DEBUG_H
#define DEBUG_H

#include "string.h"

/* dump_registers:
 * Writes the contents of the general registers to the
 * terminal in a human-readable format
 */
void dump_registers()
{
  u32int eax_val = 0;
  u32int ebx_val = 0;
  u32int ecx_val = 0; 
  u32int edx_val = 0;
    
  asm volatile ( "movl %%eax, %0\n" : "=r"(eax_val) );
  asm volatile ( "movl %%ebx, %0\n" : "=r"(ebx_val) );
  asm volatile ( "movl %%ecx, %0\n" : "=r"(ecx_val) );
  asm volatile ( "movl %%edx, %0\n" : "=r"(edx_val) );
  
  kprintf("DEBUG: DUMPING REGISTERS\n");
  kprintf("EAX: 0x%x\tEBX: 0x%x\nECX: 0x%x\tEDX: 0x%x\n\n", eax_val, ebx_val, ecx_val, edx_val);
}

#endif