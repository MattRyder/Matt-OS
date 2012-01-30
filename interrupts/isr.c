#include "../includes/isr.h"

void isr_handler(registers_t registers)
{
    kmonitorclear();
    kprintf("A problem has been detected by MattOS and has been shut down to prevent damage to your PC.\n\n");
    kprintf("%s\n", isr_message[registers.int_no]);

    kprintf("If this is the first time this error has occurred, restart your computer.\n");
    kprintf("If this message appears again, please contact your vendor.\n\n");
    kprintf("Technical Information:\n");
    kprintf("\t0x%x\t(0x%x, 0x%x, 0x%x, 0x%x)\n", registers.int_no, registers.eax, registers.ebx, registers.ecx, registers.edx);

}
