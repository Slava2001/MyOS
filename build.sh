rm bin/*
rm os.img



nasm ./bootloader/BootLoader.asm -f bin -o bin/bootloader.bin

bcc -Iinclude -W -0 -c kernel/kernel.c -o bin/kernel.obj
bcc -Iinclude -W -0 -c lib/stdio.c -o bin/stdio.obj
bcc -Iinclude -W -0 -c lib/string.c -o bin/string.obj
bcc -Iinclude -W -0 -c lib/memory.c -o bin/memory.obj


ld86 -d bin/*.obj -o bin/os.bin

# gcc -std=gnu99 -Os -nostdlib -m32 -march=i386 -ffreestanding -o bin/kernel.bin -Wl,--nmagic,--script=util/com.ld kernel/kernel.c
dd if=bin/bootloader.bin of=os.img 
dd if=bin/os.bin of=os.img seek=1 obs=512