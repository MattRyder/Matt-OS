/* 
 * monitor.h - Manages output to the CRT/LCD monitor
 */

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

void k_putc(char c); 	//Write a single char to the screen
void k_monitorclear();  //Clear the screen to black
void k_puts(char* c);	//Write a null-terminated ASCII string to the screen

void k_colorstring(char* s, u8int attribute); //Write a colored char to the screen from the given attributes
void k_colorchar(char c, u8int attribute);    //Writes a colored string to the screen from the given attributes

#endif