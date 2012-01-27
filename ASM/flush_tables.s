[GLOBAL gdt_flush]
[GLOBAL idt_flush]

gdt_flush:
  cli
  mov eax, [esp+4]
  lgdt [eax]

  mov eax, CR0		;move the contents of control register 0 into EAX
  or AL, 1		;set bit 0 to 1, 'protected mode enable' bit
  mov CR0, eax		;move it back, protected mode is now set!

  mov ax, 0x10		;GDT Data Segment offset is at 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:.flushGDT	;far jump to 0x08 for Code Segment

.flushGDT:
  ret			;GDT Flushed - Return to Kernel!


;Flush the IDT and load the one the OS sets up:
idt_flush:
  mov eax, [esp+4]
  lidt [eax]
  ret 			;IDT Flushed - Return to Kernel!

