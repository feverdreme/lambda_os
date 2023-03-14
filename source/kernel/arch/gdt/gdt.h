#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// https://wiki.osdev.org/GDT

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    unsigned int limit_high : 4;
    unsigned int flags : 4;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    struct gdt_entry* base;
} __attribute__((packed));

struct gdt_entry gdt[5];
struct gdt_ptr gp;

// void set_gdt(uint32_t limit, stuct gdt_entry* base);

void set_gdt();
void gdt_reload();

// Declared because this will only ever be used once
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].limit_high = (limit >> 16) & 0b1111; // We only want the 4 bits
    gdt[num].flags = flags;

    /* Finally, set up the granularity and access flags */
    gdt[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install() {
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gp.base = (struct gdt_entry*)&gdt;

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    // Kernel Mode Code Segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0b1010);

    // Kernel Mode Data Segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0b1100);

    // User Mode Code Segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0b1010);

    // User Mode Data Segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0b1100);

    /* Flush out the old GDT and install the new changes! */
    // set_gdt(gp.limit, gp.base);

    set_gdt();
    gdt_reload();
}

#endif