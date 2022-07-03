GDT_Start:
    null_descriptor:
        dd 0
        dd 0
    
    code_descriptor:
        dw 0xffff ; first 16 bits of limit
        db 0, 0, 0 ; first 24 bits of the base
        db 10011010b ; flags (pres, priv, type, type flags)
        db 11001111b ; last 4 bits of flags + last 4 bits of limit
        db 0 ; last 8 bits of base

    data_descriptor:
        dw 0xffff ; first 16 bits of limit
        db 0, 0, 0 ; first 24 bits of the base
        db 10010010b ; flags (pres, priv, type, type flags)
        db 11001111b ; last 4 bits of flags + last 4 bits of limit
        db 0 ; last 8 bits of base

GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1 ; size
    dd GDT_Start ; ptr to start

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start