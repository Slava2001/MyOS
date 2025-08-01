.PHONY: build img run help default

BUILDDIR = ./build
IMG_NAME = ./os.img
IMG_SIZE_MB = 16 # Range: 16Mb - 2G
BOOTLOADER_SIZE_SECTORS = 10

default: help

help:
	@echo "Available commands:"
	@echo "  make build   - compile the project"
	@echo "  make img     - create a disk image"
	@echo "  make run     - run the OS in qemu"

build: create_builddir build_mbr
	@echo "[build] Compiling the project: OK"

create_builddir:
	@mkdir -p $(BUILDDIR)

build_mbr: ./src/main_boot_record.asm
	@nasm ./src/main_boot_record.asm -f bin -o $(BUILDDIR)/mbr.bin
	@echo "[build] Compiling the MBR: OK"

img:
	@rm -f $(IMG_NAME)
	@echo "[img] Remove old image: OK"
	@dd if=/dev/zero of=$(IMG_NAME) bs=1MiB count=$(IMG_SIZE_MB) > /dev/null 2>&1  
	@echo "[img] Creating empty disk image: OK"
	@mkfs.fat -F 16 -R $(BOOTLOADER_SIZE_SECTORS) $(IMG_NAME) > /dev/null 2>&1 
	@echo "[img] Creating fat16 file system: OK"
	@dd if=$(BUILDDIR)/mbr.bin of=$(IMG_NAME) bs=1 count=3 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1 
	@dd if=$(BUILDDIR)/mbr.bin of=$(IMG_NAME) skip=62 seek=62 bs=1 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1 
	@echo "[img] Writing MBR: OK"
	@echo "[img] Creating disk image: OK"

run: build img
	@echo "[run] Running in emulator..."
	@sudo qemu-system-x86_64 -hda $(IMG_NAME) > /dev/null 2>&1 

