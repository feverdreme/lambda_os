[bits 16]
[org 0x7c00]

; CONSTANTS
KERNEL_ENTRY equ 0x1000

jmp start_realmode

BOOT_DISK: db 0

start_realmode:
    ; initialize stack
    mov bp, 0x8000
    mov sp, bp

    ; reset data and extra segment pointer to 0
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; read the kernel
    mov bx, KERNEL_ENTRY
    mov dh, 0x20

    mov ah, 0x02
    mov al, dh ; number of sectors you want to read
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
    int 0x13

    ; clear screen
    mov ah, 0x0
    mov al, 0x13 ; 320x200 256 color graphics
    int 0x10

    ; setup for 32 bit
    cli ; disable interrupts
    lgdt [GDT_Descriptor] ; load the gdt

    ; change last bit of cr0 to 1
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEG:start_protectedmode
    jmp $

[bits 32]
start_protectedmode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; stack but 32 bit
    mov ebp, 0x90000
    mov esp, ebp

    ; kernel entry
    jmp KERNEL_ENTRY

%include "boot/gdt_table.inc"

; boot padding to 512 bytes
; 510 is in this expression because the last two bytes are for the magic number
times 510-($-$$) db 0

; tells bios its bootable
dw 0xaa55