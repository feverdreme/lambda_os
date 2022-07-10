ASM := nasm
CC := i686-elf-gcc
CFLAGS := -Wall -Wextra -Wpedantic -isystem include -ffreestanding -m32 -g
LD := i686-elf-ld

# LINKED_OBJECTS := $(wildcard bin/objects/*.o)

.PHONY: all clean
.PHONY: fonts

all: bootloader kernel libraries zero_padding
#	$(LD) -Ttext 0x1000 bin/kernel_entry.o $(wildcard bin/objects/*.o) -o bin/kernel.bin --oformat binary
	$(LD) -Ttext 0x1000 bin/kernel_entry.o bin/objects/*.o -o bin/kernel.bin --oformat binary


	cat bin/boot.bin bin/kernel.bin bin/zero_padding.bin > bin/os.bin

include extra/mk/bootloader.mk
include extra/mk/kernel.mk
include extra/mk/libraries.mk
include extra/mk/extra.mk

clean:
	rm bin/boot.bin bin/zero_padding.bin bin/kernel.bin bin/kernel_entry.o bin/objects/* kernel/graphics/*.o include/libc/*.o include/fonts/*.o