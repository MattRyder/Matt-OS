/* Common.h
 * Common functions for the kernel */

#ifndef COMMON_H
#define COMMON_H

/* CGA COLOR REFERENCE
0 	black
1 	blue
2 	green
3	cyan
4	red
5	magenta
6	brown
7	light gray
8	gray
9	light blue
10 	light green
11	light cyan
12	light red
13	light magenta
14	yellow
15	white (high intensity)
*/


//Standardized typedefs for x86 platforms
typedef unsigned int	 u32int;
typedef 	     int	 s32int;
typedef unsigned short   u16int;
typedef 	     short   s16int;
typedef unsigned char	 u8int;
typedef          char    s8int;


void outb( u16int port, u8int value );
u8int inb( u16int port );
u16int inw ( u16int port);

#endif
