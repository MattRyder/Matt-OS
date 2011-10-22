#include "../includes/common.h"

void outb( u16int port, u8int value )
{
  asm volatile ( "outb %1, %0" : : "dN" (port), "a" (value) );
}

u8int inb( u16int port )
{
  u8int x;
  asm volatile ( "inb %1, %0" : "=a" (x) : "dN" (port) );
  return x;
}

u16int inw ( u16int port)
{
  u16int x;
  asm volatile ( "inw %1, %0" : "=a" (x) : "dN" (port) );
  return x;
}
