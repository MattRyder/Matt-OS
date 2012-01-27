#include "kernel.h"

/* xmain:
 * MAIN ENTRY POINT FROM THE BOOTLOADER
 */
void xmain( void* mbd, unsigned int magic )
{
  if( magic != 0x2BADB002 ) {
    kprintf("[SYSTEM] GRUB Magic: \n");
  }

  //Initialize the Global Descriptor Table:
  //init_tables();
  print_welcome_message();
  //kprintf("[SYSTEM] GRUB Magic: %s OK\n", kitohex(magic));
  kprintf("[USER] kitohex:\n\tExpected: 0xF00\n\tActual:0x%s\n", kitohex(3840));
  kprintf("[USER] kitohex:\n\tExpected: 0xBEEFED\n\tActual: 0x%x", 12513261);
  //asm volatile ("int $1");
}

/* print_welcome_message:
 * Outputs a cheery welcome message to the terminal!
 */
void print_welcome_message()
{
  kmonitorclear();
  kprintf("Matt's Operating System - v%s\n\n", kVersion());
}
