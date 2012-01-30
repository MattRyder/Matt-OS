;Interrupt.h - Interrupt handler

;defined in isr.h
[EXTERN isr_handler]

%macro ISR_NOERR 1
[GLOBAL isr%1]
  isr%1:
  cli
  push byte 0
  push byte %1
  jmp isr_common_stub
%endmacro

%macro ISR_ERROR 1
[GLOBAL isr%1]
  isr%1:
  cli
  push byte %1
  jmp isr_common_stub
%endmacro

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERROR 8
ISR_NOERR 9
ISR_ERROR 10
ISR_ERROR 11
ISR_ERROR 12
ISR_ERROR 13
ISR_ERROR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

;Function to save the stack, handle the interrupt then resume stack operation.
isr_common_stub:
  pusha			;push the registers onto the stack

  mov ax, ds		;push the 16-bits of the data segment descriptor to AX, and onto the stack.
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call isr_handler

  ;reload the original data segment descriptor
  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa			;Pop all the registers off the stack
  add esp, 8		;clear the int from the stack ptr
  sti 			;start interrupts again!
  iret			;return to caller
