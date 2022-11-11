# Build tools and flags
SHELL := /bin/bash -O globstar
ASM := nasm
CC := i686-elf-gcc
CFLAGS := -Wall -Wextra -Wpedantic -isystem include -ffreestanding -m32 -g
LD := i686-elf-ld
OBJCOPY := i686-elf-objcopy

###############################################################################
# Stages

# 1. boot/boot.asm -> bin conversion
# 2. General *.{asm, c} -> *.{asm.o, c.o} compilation (explicit)
# 3. Object linkage (objects from step 2) 
# 4. kernel/kernel_entry.asm and kernel/kernel_main.c compilation
# 5. Kernel linkage
# 6. kernel.elf -> kernel.bin
# 7. zero-padding generation
# 8. concatenation into OS.bin

# 9. cleaning

##############################################################################
# Stage lists

# Never EVER switch the order of these two
KERNEL_SPECIAL_O = kernel/kernel_entry.asm.o kernel/kernel_main.c.o 

GENERAL_ASMC_DIRS =
GENERAL_ASMC_DIRS += kernel/idt kernel/gdt kernel/graphics
GENERAL_ASMC_DIRS += include/libc include/fonts

GENERAL_ASM_SRC := $(foreach dir, $(GENERAL_ASMC_DIRS), $(wildcard $(dir)/*.asm))
GENERAL_C_SRC := $(foreach dir, $(GENERAL_ASMC_DIRS), $(wildcard $(dir)/*.c))

GENERAL_ASM_O := $(patsubst %.asm, %.asm.o, $(GENERAL_ASM_SRC))
GENERAL_C_O := $(patsubst %.c, %.c.o, $(GENERAL_C_SRC))

GENERAL_ASMC_BIN_DIRS_O := $(patsubst %, bin/objects/%.o, $(GENERAL_ASMC_DIRS))

##############################################################################
all: os.bin

# Stage 1
bin/boot.bin:
	@echo "STAGE 1..."
	$(ASM) boot/boot.asm -f bin -o bin/boot.bin
	@echo 

# Stages 2 & 3
$(GENERAL_ASMC_BIN_DIRS_O): $(GENERAL_ASM_O) $(GENERAL_C_O)
	mkdir -p $(@D)
	$(LD) -relocatable -o $@ $(patsubst bin/objects/%.o, %, $@)/*.o

# Stages 4 & 5
bin/kernel.elf: $(KERNEL_SPECIAL_O) $(GENERAL_ASMC_BIN_DIRS_O)
	$(LD) -T extra/ld/linker.ld $(KERNEL_SPECIAL_O) $(GENERAL_ASM_O) $(GENERAL_C_O)

# Stage 6
bin/kernel.bin: bin/kernel.elf
	$(OBJCOPY) -O binary bin/kernel.elf bin/kernel.bin

# Stage 7
bin/zero_padding.bin:
	echo "times 10240 db 0" > kernel/zero_padding.asm
	$(ASM) kernel/zero_padding.asm -f bin -o bin/zero_padding.bin

# Stage 8
os.bin: bin/boot.bin bin/kernel.bin bin/zero_padding.bin
	cat bin/boot.bin bin/kernel.bin bin/zero_padding.bin > bin/os.bin

	$(OBJCOPY) --only-keep-debug bin/kernel.elf bin/kernel.sym

##############################################################################
# GENERAL C & ASM RULES

%.c.o:
	@echo "COMPILING $@" 
	$(CC) $(CFLAGS) -c $(@:.c.o=.c) -o $@
	@echo

%.asm.o:
	@echo "COMPILING $@" 
	$(ASM) -f elf $(@:.asm.o=.asm) -o $@
	@echo

##############################################################################
# CLEANING AND RESETTING
clean:
	rm $(GENERAL_ASM_O) $(GENERAL_C_O) $(KERNEL_SPECIAL_O)
	rm -r bin/objects/*

reset:
	rm bin/*.bin 
	rm bin/kernel.*