LIBC_SRC := $(wildcard include/libc/*.c)
LIBC_O := $(patsubst %.c,%.o,$(LIBC_SRC))

.PHONY: libraries libc

############################################################################
# LIBC BUILD
libraries: libc

libc: $(LIBC_O)
	$(LD) -relocatable $(LIBC_O) -o bin/objects/libc.o

############################################################################