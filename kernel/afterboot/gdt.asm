[extern gp]

global _gdt_flush
_gdt_flush:
    lgdt [gp]
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
    
    flush2:
        ret               