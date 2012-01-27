#ifndef STRING_H
#define STRING_H

#include "common.h"
#include "stdargs.h"
#include "monitor.h"

char toHexChar(s32int n);
char toHex(s32int n);

void* memset(void *dest, int c, size_t size);
void* memcpy(void *dest, void *src, size_t size);

int strlen(const char* str);

void kitoa(s32int n);
char* kitohex(s32int n);

void kprintf(const s8int *printf_format, ...);
#endif
