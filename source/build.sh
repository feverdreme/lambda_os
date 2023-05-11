export PATH="/home/jeffrey/opt/cross64/bin:/home/jeffrey/opt/cross/bin:$PATH"

make os64 V=1
# qemu-system-x86_64 -drive format=raw,file="bin/os.bin",index=0,if=floppy, -m 128M # -s -S
qemu-system-x86_64 -drive format=raw,file="build/lambda_os.iso" -m 4G -s -S

make clean
make reset