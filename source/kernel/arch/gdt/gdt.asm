[bits 64]
[extern gp]

global set_gdt
global gdt_reload

set_gdt:
    LGDT  [gp]
    RET

gdt_reload:
    ; Reload CS register:
    push 0x08                 ; Push code segment to stack, 0x08 is a stand-in for your code segment
    lea RAX, [rel .reload_CS] ; Load address of .reload_CS into RAX
    push RAX                  ; Push this value to the stack
    retfq                     ; Perform a far return, RETFQ or LRETQ depending on syntax

.reload_CS:
    ; Reload data segment registers
    MOV   AX, 0x10 ; 0x10 is a stand-in for your data segment
    MOV   DS, AX
    MOV   ES, AX
    MOV   FS, AX
    MOV   GS, AX
    MOV   SS, AX
    RET

; global _gdt_flush
; _gdt_flush:
;     lgdt [gp]
;     mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     mov ss, ax
;     jmp 0x08:flush2
    
;     flush2:
;         ret