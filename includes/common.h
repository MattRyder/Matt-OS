/* Common.h
 * Common functions for the kernel */

#ifndef COMMON_H
#define COMMON_H

// CGA Enum for referencing colors in the OS.
enum CGA {
  BLACK         = 0, 
  BLUE          = 1, 
  GREEN         = 2, 
  CYAN          = 3,
  RED           = 4,
  MAGENTA       = 5,
  BROWN         = 6,
  LIGHT_GRAY    = 7,
  GRAY          = 8,
  LIGHT_BLUE    = 9,
  LIGHT_GREEN   = 10,
  LIGHT_CYAN    = 11,
  LIGHT_RED     = 12,
  LIGHT_MAGENTA = 13,
  YELLOW        = 14,
  WHITE         = 15
};

//Standardized typedefs for x86_32 platforms
typedef unsigned int	 u32int;
typedef 	 int	 s32int;
typedef unsigned short   u16int;
typedef 	 short   s16int;
typedef unsigned char	 u8int;
typedef          char    s8int;

typedef unsigned long	 size_t;


void outb( u16int port, u8int value );
u8int inb( u16int port );
u16int inw ( u16int port);

#endif
