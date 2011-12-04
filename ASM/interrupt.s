;Interrupt.h - Interrupt handler

%macro ISR_NOERROR 1
[GLOBAL isr%1]
  isr%1:
  cli
  push byte 0
  push byte %1
  jmp isr_common_stub
%endmacro

%macro ISR_ERRORCODE 1
[GLOBAL isr%1]
  isr%1:
  cli
  push byte %1
  jmp isr_common_stub
%endmacro

ISR_NOERROR 0
ISR_NOERROR 1
ISR_NOERROR 2
ISR_NOERROR 3
ISR_NOERROR 4
ISR_NOERROR 5
ISR_NOERROR 6
ISR_NOERROR 7
ISR_ERRORCODE 8
ISR_NOERROR 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERROR 15
ISR_NOERROR 16
ISR_NOERROR 17
ISR_NOERROR 18
ISR_NOERROR 19
ISR_NOERROR 20
ISR_NOERROR 21
ISR_NOERROR 22
ISR_NOERROR 23
ISR_NOERROR 24
ISR_NOERROR 25
ISR_NOERROR 26
ISR_NOERROR 27
ISR_NOERROR 28
ISR_NOERROR 29
ISR_NOERROR 30
ISR_NOERROR 31

;defined in isr.h
[EXTERN isr_handler]

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
