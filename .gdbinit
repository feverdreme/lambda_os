target remote localhost:1234
set disassembly-flavor intel
add-symbol-file source/kernel.elf

break main