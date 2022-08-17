KERNEL_GRAPHICS_SRC := $(wildcard kernel/graphics/*.c)
KERNEL_GRAPHICS_O := $(patsubst %.c,%.o,$(KERNEL_GRAPHICS_SRC))

KERNEL_AFTERBOOT_ASM_SRC := $(wildcard kernel/afterboot/*.asm)
KERNEL_AFTERBOOT_ASM_O := $(patsubst %.asm,%.asm.o,$(KERNEL_AFTERBOOT_ASM_SRC))
KERNEL_AFTERBOOT_C_SRC := $(wildcard kernel/afterboot/*.asm)
KERNEL_AFTERBOOT_C_O := $(patsubst %.c,%.c.o,$(KERNEL_AFTERBOOT_C_SRC))

.PHONY: kernel kernel_entry kernel_graphics kernel_main 

############################################################################
# KERNEL BUILD
kernel: kernel_entry kernel_main kernel_graphics kernel_afterboot
#	$(LD) -Ttext 0x1000 bin/kernel_entry.o bin/objects/*.o -o bin/kernel.elf --oformat elf32-i386
	$(LD) -T extra/ld/linker.ld bin/kernel_entry.o bin/objects/*.o 

	$(OBJCOPY) -O binary bin/kernel.elf bin/kernel.bin

kernel_entry:
	$(ASM) -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o

kernel_main:
	$(CC) $(CFLAGS) -c kernel/kernel_main.c -o bin/objects/kernel_main.o

kernel_graphics: $(KERNEL_GRAPHICS_O)
	$(LD) -relocatable $(KERNEL_GRAPHICS_O) -o bin/objects/graphics.o

kernel_afterboot: $(KERNEL_AFTERBOOT_C_O) $(KERNEL_AFTERBOOT_ASM_O)
	$(LD) -relocatable $(KERNEL_AFTERBOOT_SRC_O) $(KERNEL_AFTERBOOT_ASM_O) -o bin/objects/afterboot.o

$(FONTS_O) $(KERNEL_AFTERBOOT_ASM_O):
	$(ASM) -f elf $(patsubst %.asm.o,%.asm,$@) -o $@

$(KERNEL_AFTERBOOT_C_O):
	$(CC) $(CFLAGS) -c $(patsubst %.c.o,%.c,$@) -o $@
############################################################################