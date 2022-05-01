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
sudo touch myos/file1.txt
sudo touch myos/file2.txt
sudo touch myos/file3.txt
sudo touch myos/file4.txt
sudo touch myos/file5.txt
sudo mkdir myos/dir1
sudo mkdir myos/dir2
sudo mkdir myos/dir3
sudo mkdir myos/dir4
sudo mkdir myos/dir5
sudo sync
sudo umount ./myos
