KERNEL_GRAPHICS_SRC := $(wildcard kernel/graphics/*.c)
KERNEL_GRAPHICS_O := $(patsubst %.c,%.o,$(KERNEL_GRAPHICS_SRC))

.PHONY: kernel kernel_entry kernel_graphics kernel_main 

############################################################################
# KERNEL BUILD
kernel: kernel_entry kernel_main kernel_graphics

kernel_entry:
	$(ASM) -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o

kernel_main:
	$(CC) $(CFLAGS) -c kernel/kernel_main.c -o bin/objects/kernel_main.o

kernel_graphics: $(KERNEL_GRAPHICS_O)
	$(LD) -relocatable $(KERNEL_GRAPHICS_O) -o bin/objects/graphics.o

############################################################################