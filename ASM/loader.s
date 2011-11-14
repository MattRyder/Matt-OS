; ***********************************
;           GRUB Kernel Loader
; ***********************************

global loader			;Making the entry point visible to the linker
extern xmain

;Set up the GRUB multiboot header
MODULEALIGN 	equ 1<<0
MEMINFO		equ 1<<1
FLAGS		equ MODULEALIGN | MEMINFO
MAGIC		equ 0X1BADB002
CHECKSUM	EQU -(MAGIC + FLAGS)

section .text
align 4
MultiBootHeader:
  dd MAGIC
  dd FLAGS
  dd CHECKSUM

;Reserve space for the stack!
STACKSIZE equ 0x4000		;A whole 16K for the stack

loader:
  mov esp, stack+STACKSIZE
  push eax			;Pass the Multiboot MAGIC to the bootloader
  push ebx			;Pass the FLAGS to the bootloader

  call xmain			;Then call the actual kernel.
  cli

hang:
  hlt
  jmp hang

section .bss
align 4
stack:	resb STACKSIZE 		;Reserve that 16K for the stack 