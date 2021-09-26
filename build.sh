nasm ./bootloader/BootLoader.asm -f bin -o bin/bootloader.bin
gcc -std=gnu99 -Os -nostdlib -m32 -march=i386 -ffreestanding -o bin/kernel.bin -Wl,--nmagic,--script=com.ld kernel/kernel.c
dd if=bin/bootloader.bin of=os.img 
dd if=bin/kernel.bin of=os.img seek=1 obs=512