#include "includes/monitor.h"
#include "includes/version.h"
#include "kernel.h"
#include "includes/string.h"
#include "includes/debug.h"

/* xmain:
 * MAIN ENTRY POINT FROM THE BOOTLOADER
 */
void xmain( void* mbd, unsigned int magic )
{
  
  if( magic != 0x2BADB002 )
  {
    //Output an error! [THIS IS NEVER HIT! USE ASM TO DO THIS IN LOADER.S!]
    kprintf("Something went wrong! Didn't get GRUB MAGIC [0x2BADB002]");
  }
  print_welcome_message(); 
  
}

/* print_welcome_message:
 * Outputs a cheery welcome message to the terminal!
 */
void print_welcome_message()
{
  k_monitorclear();
  kprintf("Welcome to Matt's Operating System - v%s\n\n", kVersion());
}
