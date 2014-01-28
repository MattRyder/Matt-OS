#include "../includes/isr.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int irq_no, isr_t handler)
{
  interrupt_handlers[irq_no] = handler;
}

void isr_handler(registers_t registers)
{
  kprintf("\t0x%x\t(0x%x, 0x%x, 0x%x, 0x%x)\n", registers.int_no, registers.eax, registers.ebx, registers.ecx, registers.edx);
}

void irq_handler(registers_t registers)
{
  if (registers.int_no >= 40)
  {
    // Send reset to Slave IRQ
    outb(0xA0, 0x20);
  }

  // Send a reset to Master IRQ
  outb(0x20, 0x20);

  if (interrupt_handlers[registers.int_no] != 0)
  {
    isr_t handler = interrupt_handlers[registers.int_no];
    handler(registers);
  }
}
