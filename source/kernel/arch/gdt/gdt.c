#include "gdt.h"

struct gdt_entry gdt[5];
struct gdt_ptr gp;

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