# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := kernel.elf

# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.

ARCH := x86_64-elf

override ASM := nasm
override CC := $(ARCH)-gcc
override CCP := $(ARCH)-g++ -std=c++0x
override LD := $(ARCH)-ld
override AR := $(ARCH)-ar
override OBJCOPY := $(ARCH)-objcopy
override STRIP := $(ARCH)-strip
override LDSCRIPT := ld/limine_linker.ld

# User controllable C flags.
override DEFAULT_CFLAGS := -g -O2 -pipe
$(eval $(call DEFAULT_VAR,CFLAGS,$(DEFAULT_CFLAGS)))

# User controllable C preprocessor flags. We set none by default.
override DEFAULT_CPPFLAGS :=
$(eval $(call DEFAULT_VAR,CPPFLAGS,$(DEFAULT_CPPFLAGS)))

# User controllable nasm flags.
override DEFAULT_NASMFLAGS := -F dwarf -g
$(eval $(call DEFAULT_VAR,NASMFLAGS,$(DEFAULT_NASMFLAGS)))

# User controllable linker flags. We set none by default.
override DEFAULT_LDFLAGS :=
$(eval $(call DEFAULT_VAR,LDFLAGS,$(DEFAULT_LDFLAGS)))

# Internal C flags that should not be changed by the user.
override CFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fno-PIE \
    -fno-PIC \
    -m64 \
    -march=x86-64 \
    -mabi=sysv \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone \
    -mcmodel=kernel

# special include paths
override CFLAGS += -isystem include -isystem kernel

# Internal C preprocessor flags that should not be changed by the user.
override CPPFLAGS := \
    -I. \
    $(CPPFLAGS) \
    -MMD \
    -MP

# Internal linker flags that should not be changed by the user.
override LDFLAGS += \
    -nostdlib \
    -static \
    -m elf_x86_64 \
    -z max-page-size=0x1000 \
    -T $(LDSCRIPT)

# Check if the linker supports -no-pie and enable it if it does.
ifeq ($(shell $(LD) --help 2>&1 | grep 'no-pie' >/dev/null 2>&1; echo $$?),0)
    override LDFLAGS += -no-pie
endif

# Internal nasm flags that should not be changed by the user.
override NASMFLAGS += \
    -Wall \
    -f elf64

override CFILES := $(shell find -L kernel include -type f -name '*.c')
override CPPFILES := $(shell find -L kernel include -type f -name '*.cpp')
override NASMFILES := $(shell find -L kernel include -type f -name '*.asm')
override OBJ := $(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o) $(NASMFILES:.asm=.asm.o)
override HEADER_DEPS := $(CFILES:.c=.c.d) $(CPPFILES:.cpp=.cpp.d)

# Default target.
.PHONY: all
all: $(KERNEL)

limine.h:
	curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

# Compilation rules for *.int.c files
%.int.c.o: %.int.c limine.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -mgeneral-regs-only -c $< -o $@

# Compilation rules for *.c files.
%.c.o: %.c limine.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%.cpp.o: %.cpp limine.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
%.asm.o: %.asm
	$(ASM) $(NASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f limine.h
