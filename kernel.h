#ifndef KERNEL_H
#define KERNEL_H

#include "includes/monitor.h"
#include "includes/gdt.h"
#include "includes/version.h"
#include "includes/string.h"
#include "includes/debug.h"

void xmain( void* mbd, unsigned int magic );
void print_welcome_message();

#endif