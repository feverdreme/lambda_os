make V=1
make clean
qemu-system-x86_64 -drive format=raw,file="bin/os.bin",index=0,if=floppy, -m 128M
# make clean