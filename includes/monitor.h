/*
 * monitor.h - Manages output to the CRT/LCD monitor
 */

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

void kputc(char c); 	//Write a single char to the screen
void kmonitorclear();  //Clear the screen to black
void kputs(char* c);	//Write a null-terminated ASCII string to the screen

void colorstring(char* s, u8int attribute); //Write a colored char to the screen from the given attributes
void colorchar(char c, u8int attribute);    //Writes a colored string to the screen from the given attributes

#endif
