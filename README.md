# Lambda OS

The official github repository of the lambda_os project. This is my Severn Van Eney '09 Fellows Project, where I'm developing the kernel that will interop with my bespoke hardware.

## Bugs and Fixes

(In no particular order)

[ ] `puts.c` has bug where it assumes `pos_x == 0` if there is a forced newline due to line wrapping

[ ] `kmalloc` is inefficient, must redesign

[ ] Makefile doesn't support a cpp kernel

[ ] Remove all explicitly 32bit code in preparation for 64bit mode

## Features and Todo

[ ] Memory manager has `kfree` implemented

[ ] Memory manager has `kmove` and other memory functions implemented

[ ] `crt.0` and other libraries are linked automatically, instead of being linked in the linker script they become a build step before kernel linkage

[ ] Prepare makefile for BOOTBOOT protocol and linkage

[ ] Migrate bss to be a c-defined allocation, and should correspond with the linker section

[ ] Make `libc` and `font` a shared static library to be linked last (ie. `libc.so` `font.so`)

[ ] Migrate to BOOTBOOT

[ ] Reformat project architecture to scale for kernel code and misc

[ ] Basic window prototype done

[ ] Add more stuff to the `README`

[ ] Add doxygen autogeneration

[ ] Add doxygen comments to all functions

[ ] Add documentation and notes on how kernel will interop with LCD and keyboard
