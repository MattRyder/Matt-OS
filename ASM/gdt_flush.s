[GLOBAL gdt_flush]

gdt_flush:
  mov eax, [esp+4]
  lgdt [eax]
  
  mov ax, 0x10		;GDT Data Segment offset is at 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:.flushGDT	;far jump to 0x08 for Code Segment

.flushGDT:
  ret			;GDT Flushed - Return to Kernel!

  