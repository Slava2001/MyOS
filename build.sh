set -Eeo pipefail

someFaile() {
    echo -e "\033[31mSome Err :(\033[0m"
}
trap someFaile ERR

rm os.img -f

# compile bootloader
nasm ./bootloader/BootLoader.asm -f bin -o bin/bootloader.bin

# compile kernel main
bcc -Iinclude -W -0 -c kernel/kernel.c -o bin/kernel.mainobj -ansi
# compile stdio lib
bcc -Iinclude -W -0 -c lib/stdio.c -o bin/stdio.obj -ansi
# compile string lib
bcc -Iinclude -W -0 -c lib/string.c -o bin/string.obj -ansi
# compile memory lib
bcc -Iinclude -W -0 -c lib/memory.c -o bin/memory.obj -ansi
# compile fat16 lib
bcc -Iinclude -W -0 -c lib/fat16.c -o bin/fat16.obj -ansi
# compile math lib
bcc -Iinclude -W -0 -c lib/math.c -o bin/math.obj -ansi

# link os
ld86 -d bin/kernel.mainobj bin/*.obj -o bin/os.bin

# Check OS size. Current bootloader can only load 20*512=10240 bytes
FILENAME=bin/os.bin
FILESIZE=$(stat -c%s "$FILENAME")
if [[ FILESIZE -gt 10000 ]]; then # 20 sectors (240 byte reserve)
  echo -e "\033[31mYou got the right input. Size: "$FILESIZE"\033[0m"
fi

# write bootloader 
dd if=bin/bootloader.bin of=os.img obs=1 count=3 iflag=skip_bytes,count_bytes
dd if=bin/bootloader.bin of=os.img obs=1 skip=62 seek=62 iflag=skip_bytes,count_bytes

# write os
dd if=bin/os.bin of=os.img obs=512 seek=1
