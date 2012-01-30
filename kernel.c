#include "kernel.h"

/* xmain:
 * MAIN ENTRY POINT FROM THE BOOTLOADER
 */
void xmain( void* mbd, unsigned int magic )
{
    print_welcome_message();

    kprintf("[SYSTEM] GRUB Magic OK: 0x%s\n", kitohex(magic));
    init_tables(); //Initialize the Global Descriptor Table

    asm volatile("int $0x04");

}

/* print_welcome_message:
 * Outputs a cheery welcome message to the terminal!
 */
void print_welcome_message()
{
  kmonitorclear();
  kprintf("Matt's Operating System - v%s\n\n", kVersion());
}
