.PHONY: zero_padding

############################################################################
# EXTRA

zero_padding:
	@echo "times 10240 db 0" > kernel/zero_padding.asm
	$(ASM) kernel/zero_padding.asm -f bin -o bin/zero_padding.bin

############################################################################