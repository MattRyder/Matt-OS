#include "../includes/isr.h"

void isr_handler(registers_t registers)
{
  kprintf("Recieved Interrupt: %i\n", registers.int_no);
}