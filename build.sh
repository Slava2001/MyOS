rm bin/*
rm os.img

nasm ./bootloader/BootLoader.asm -f bin -o bin/bootloader.bin

bcc -Iinclude -W -0 -c kernel/kernel.c -o bin/kernel.obj
bcc -Iinclude -W -0 -c lib/stdio.c -o bin/stdio.obj
bcc -Iinclude -W -0 -c lib/string.c -o bin/string.obj
bcc -Iinclude -W -0 -c lib/memory.c -o bin/memory.obj


ld86 -d bin/*.obj -o bin/os.bin

dd if=bin/bootloader.bin of=os.img obs=1 count=3 iflag=skip_bytes,count_bytes
dd if=bin/bootloader.bin of=os.img obs=1 skip=62 seek=62 iflag=skip_bytes,count_bytes
dd if=bin/os.bin of=os.img seek=1 obs=512 

# sudo dd if=bin/bootloader.bin of=/dev/sdb obs=1 count=3 iflag=skip_bytes,count_bytes
# sudo dd if=bin/bootloader.bin of=/dev/sdb obs=1 skip=62 seek=62 iflag=skip_bytes,count_bytes
# sudo dd if=bin/os.bin of=/dev/sdb seek=1 obs=512 
