make os64.bin V=1
# qemu-system-x86_64 -drive format=raw,file="bin/os.bin",index=0,if=floppy, -m 128M # -s -S
qemu-system-x86_64 -drive format=raw,file="bin/lambda_os.img" -m 128M # -s -S

make clean
make reset