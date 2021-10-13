rm bin/*
# rm os.img

nasm ./bootloader/BootLoader.asm -f bin -o bin/bootloader.bin

bcc -Iinclude -W -0 -c kernel/kernel.c -o bin/kernel.mainobj
bcc -Iinclude -W -0 -c lib/stdio.c -o bin/stdio.obj
bcc -Iinclude -W -0 -c lib/string.c -o bin/string.obj
bcc -Iinclude -W -0 -c lib/memory.c -o bin/memory.obj
bcc -Iinclude -W -0 -c lib/fat16.c -o bin/fat16.obj
bcc -Iinclude -W -0 -c lib/graphic.c -o bin/graphic.obj


ld86 -d bin/kernel.mainobj -d bin/*.obj -o bin/os.bin

FILENAME=bin/os.bin
FILESIZE=$(stat -c%s "$FILENAME")

if [[ "$FILESIZE" > "5100" ]]; then
  echo -e "\033[31mYou got the right input.\033[0m"
fi

# dd if=bin/bootloader.bin of=os.img obs=1 count=3 iflag=skip_bytes,count_bytes
#dd if=bin/bootloader.bin of=os.img obs=1 count=512 iflag=skip_bytes,count_bytes
# dd if=bin/bootloader.bin of=os.img obs=1 skip=62 seek=62 iflag=skip_bytes,count_bytes
#dd if=bin/os.bin of=os.img seek=1 obs=512 
#dd if=../dskgen/os.img of=os.img skip=11 seek=11  obs=512

sudo dd if=bin/bootloader.bin of=/dev/mmcblk2 obs=1 count=3 iflag=skip_bytes,count_bytes
sudo dd if=bin/bootloader.bin of=/dev/mmcblk2 obs=1 skip=62 seek=62 iflag=skip_bytes,count_bytes
sudo dd if=bin/os.bin of=/dev/mmcblk2 seek=1 obs=512 
