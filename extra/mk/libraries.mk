LIBC_SRC := $(wildcard include/libc/*.c)
LIBC_O := $(patsubst %.c,%.o,$(LIBC_SRC))
FONTS_SRC := $(wildcard include/fonts/*.asm)
FONTS_O := $(patsubst %.asm,%.o,$(FONTS_SRC))

.PHONY: libraries libc fonts

############################################################################
# LIBC BUILD
libraries: libc fonts

libc: $(LIBC_O)
	$(LD) -relocatable $(LIBC_O) -o bin/objects/libc.o

fonts: $(FONTS_O)
	$(LD) -relocatable $(FONTS_O) -o bin/objects/fonts.o

# TODO: Explicit asm rules to be defined with wildcard
$(FONTS_O):
	$(ASM) -f elf $(patsubst %.o,%.asm,$@) -o $@

############################################################################