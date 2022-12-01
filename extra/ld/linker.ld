ENTRY(_start)

OUTPUT(bin/kernel.elf)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
    . = 0x1000;

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        /* bss will exist at memory location 0x3E00 */
        *(COMMON)
        *(.bss)
    }
}