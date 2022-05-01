set -Eeo pipefail

someFaile() {
    echo -e "\033[31mSome Err :(\033[0m"
}
trap someFaile ERR

rm os.hda -f
rm fat -f
# create fat 16
dd if=/dev/zero of=fat bs=$((1024*1024)) count=16 # 16MB

# make file system
mkfs.vfat -R21 -v -f2 -n FAT16 -r224 -F16 fat

# write img # I don't know how to change the learn part of the file(
dd if=bin/bootloader.bin of=os.hda obs=1 count=3 iflag=skip_bytes,count_bytes
dd if=fat of=os.hda obs=1 skip=3 seek=3 count=59 iflag=skip_bytes,count_bytes
dd if=bin/bootloader.bin of=os.hda obs=1 skip=62 seek=62 iflag=skip_bytes,count_bytes
dd if=bin/os.bin of=os.hda obs=512 seek=1 
dd if=fat of=os.hda obs=512 seek=21 skip=21

# mount 
sudo mount os.hda ./myos
sudo umount ./myos
