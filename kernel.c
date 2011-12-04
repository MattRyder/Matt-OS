#include "kernel.h"

/* xmain:
 * MAIN ENTRY POINT FROM THE BOOTLOADER
 */
void xmain( void* mbd, unsigned int magic )
{
  if( magic != 0x2BADB002 )
  {
    kprintf("Something went wrong! Didn't get GRUB MAGIC [0x2BADB002]");
  }
  
  //Initialize the Global Descriptor Table: 
  init_tables();
  print_welcome_message();
}

/* print_welcome_message:
 * Outputs a cheery welcome message to the terminal!
 */
void print_welcome_message()
{
  kmonitorclear();
  kprintf("Welcome to Matt's Operating System - v%s\n\n", kVersion());
}
