# Build tools and flags
ARCH := x86_64-elf

SHELL := /bin/bash -O globstar
ASM := nasm
CC := $(ARCH)-gcc
CCP := $(ARCH)-g++ -std=c++0x
CFLAGS := -Wall -fpic -Wextra -Wpedantic -mno-red-zone -ffreestanding -fno-stack-protector -m64 -g
CFLAGS += -isystem include -isystem kernel
LD := $(ARCH)-ld
AR := $(ARCH)-ar
OBJCOPY := $(ARCH)-objcopy
STRIP := $(ARCH)-strip
STRIPFLAGS =  -s -K mmio -K fb -K bootboot -K environment -K initstack
# LDSCRIPT := ld/bootboot.ld
LDSCRIPT := ld/bootboot.ld


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

GENERAL_ASMC_DIRS = kernel/graphics kernel/memory kernel/arch/debug
# GENERAL_ASMC_DIRS += kernel/arch/gdt kernel/arch/idt kernel/arch/debug kernel/graphics kernel/memory
GENERAL_ASMC_DIRS += include/libc include/fonts include/wmgr

GENERAL_ASM_SRC := $(foreach dir, $(GENERAL_ASMC_DIRS), $(wildcard $(dir)/*.asm))
GENERAL_C_SRC := $(foreach dir, $(GENERAL_ASMC_DIRS), $(wildcard $(dir)/*.c))
# GENERAL_CPP_SRC := $(foreach dir, $(GENERAL_ASMC_DIRS), $(wildcard $(dir)/*.cpp))

GENERAL_ASM_O := $(patsubst %.asm, %.asm.o, $(GENERAL_ASM_SRC))
GENERAL_C_O := $(patsubst %.c, %.c.o, $(GENERAL_C_SRC))
# GENERAL_CPP_O := $(patsubst %.cpp, %.cpp.o, $(GENERAL_CPP_SRC))

GENERAL_ASMC_BIN_DIRS_O := $(patsubst %, bin/objects/%.o, $(GENERAL_ASMC_DIRS))

##############################################################################
all: os32 os64

# Stage 1
bin/boot.bin:
	@echo "STAGE 1..."
	$(ASM) boot/legacy/boot.asm -f bin -o bin/boot.bin
	@echo 

# Stages 2 & 3
$(GENERAL_ASMC_BIN_DIRS_O): $(GENERAL_ASM_O) $(GENERAL_C_O) $(GENERAL_CPP_O)
	mkdir -p $(@D)
	$(LD) -relocatable -o $@ $(patsubst bin/objects/%.o, %, $@)/*.o

# Stages 4 & 5
bin/kernel.elf: $(KERNEL_SPECIAL_O) $(GENERAL_ASMC_BIN_DIRS_O)
	@echo
	@echo "LINKING..."
	$(LD) -n -nostdlib -T $(LDSCRIPT) $(KERNEL_SPECIAL_O) $(GENERAL_ASM_O) $(GENERAL_C_O) $(GENERAL_CPP_O)
	$(STRIP) $(STRIPFLAGS) bin/kernel.elf

# Stage 6
bin/kernel.bin: bin/kernel.elf
	$(OBJCOPY) -O binary bin/kernel.elf bin/kernel.bin

# Stage 7
bin/zero_padding.bin:
	echo "times 10240 db 0" > kernel/zero_padding.asm
	$(ASM) kernel/zero_padding.asm -f bin -o bin/zero_padding.bin

# Stage 8

# Option 1: 32 bit traditional
os32: bin/boot.bin bin/kernel.bin bin/zero_padding.bin
	cat bin/boot.bin bin/kernel.bin bin/zero_padding.bin > bin/os.bin

	$(OBJCOPY) --only-keep-debug bin/kernel.elf bin/kernel.sym

# Option 2: 64 bit BOOTBOOT
os64: bin/kernel.elf
	cp bin/kernel.elf build/boot/sys/core

	mkbootimg check build/boot/sys/core
	mkbootimg configuration.json initrd.rom
	mkbootimg configuration.json bootpart.bin
	mkbootimg configuration.json lambda_os.img

	mv initrd.rom build/
	mv bootpart.bin build/
	mv lambda_os.img build/
##############################################################################
# GENERAL C & ASM RULES

%.cpp.o:
	@echo "COMPILING $@" 
	$(CCP) $(CFLAGS) -c $(@:.cpp.o=.cpp) -o $@
	@echo

%.c.o:
	@echo "COMPILING $@" 
	$(CC) $(CFLAGS) -c $(@:.c.o=.c) -o $@
	@echo

%.asm.o:
	@echo "COMPILING $@" 
	$(ASM) -f elf64 $(@:.asm.o=.asm) -o $@
	@echo

##############################################################################
# CLEANING AND RESETTING
clean:
	rm $(GENERAL_ASM_O) $(GENERAL_C_O) $(GENERAL_CPP_O) $(KERNEL_SPECIAL_O)
	rm build/initrd.rom build/bootpart.bin

reset:
	rm -f bin/*.bin 
	rm -f bin/kernel.*