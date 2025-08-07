.PHONY: build img run help default

BUILDDIR = ./build
IMG_NAME = ./os.img
IMG_SIZE_MB = 16 # Range: 16Mb - 2G
SECOND_BOOTLOADER_SIZE_SECTORS = 10

default: help

help:
	@echo "Available commands:"
	@echo "  make build   - compile the project"
	@echo "  make clean   - remove compile artifacts"
	@echo "  make img     - create a disk image"
	@echo "  make run     - run the OS in qemu"

build: create_builddir mbr bootloader
	@echo "[build] Compiling the project: OK"

create_builddir:
	@mkdir -p $(BUILDDIR)

clean:
	@rm -rf $(BUILDDIR)/*

# Build main boor record

mbr: ./src/main_boot_record.asm
	@nasm ./src/main_boot_record.asm -f bin -o $(BUILDDIR)/mbr.bin
	@echo "[build] Compiling the MBR: OK"

# Build second bootloader

bootloader: bootloader_crt bootloader_main lib_all
	@ld86 -d -o $(BUILDDIR)/bootloader.bin $(BUILDDIR)/crt0.o $(BUILDDIR)/bootloader_main.o $(BUILDDIR)/*.olib
	@if [ "$$(stat -c %s $(BUILDDIR)/bootloader.bin)" -gt "$$((512 * $(SECOND_BOOTLOADER_SIZE_SECTORS)))" ]; then \
	    exit 1; \
	 fi

bootloader_crt: ./src/bootloader/crt0.asm
	@nasm ./src/bootloader/crt0.asm -f as86 -o $(BUILDDIR)/crt0.o
	@echo "[build] Compiling the crt0: OK"

bootloader_main: ./src/bootloader/main.c
	@bcc -ansi -0 -f -Iinclude -W -c ./src/bootloader/main.c -o $(BUILDDIR)/bootloader_main.o
	@echo "[build] Compiling the second bootloader main: OK"

# Build libs

lib_all: lib_stdio lib_math lib_disk lib_string

lib_stdio: ./src/lib/stdio.c ./src/lib/stdio.asm lib_math
	@bcc -ansi -0 -f -Iinclude -W -c ./src/lib/stdio.c -o $(BUILDDIR)/stdio.olib
	@nasm ./src/lib/stdio.asm -f as86 -o $(BUILDDIR)/stdio_asm.olib
	@echo "[build] Compiling the lib_stdio: OK"

lib_math: ./src/lib/math.asm
	@nasm $< -f as86 -o $(BUILDDIR)/math.olib
	@echo "[build] Compiling the lib_math: OK"

lib_disk: ./src/lib/disk.c ./src/lib/disk.asm
	@bcc -ansi -0 -f -Iinclude -W -c ./src/lib/disk.c -o $(BUILDDIR)/disk.olib
	@nasm ./src/lib/disk.asm -f as86 -o $(BUILDDIR)/disk_asm.olib
	@echo "[build] Compiling the lib_disk: OK"

lib_string: ./src/lib/string.c
	@bcc -ansi -0 -f -Iinclude -W -c ./src/lib/string.c -o $(BUILDDIR)/string.olib
	@echo "[build] Compiling the lib_string: OK"

# Create image

img:
	@rm -f $(IMG_NAME)
	@echo "[img] Remove old image: OK"
	@dd if=/dev/zero of=$(IMG_NAME) bs=1MiB count=$(IMG_SIZE_MB) > /dev/null 2>&1
	@echo "[img] Creating empty disk image: OK"
	@mkfs.fat -F 16 -R $(SECOND_BOOTLOADER_SIZE_SECTORS) $(IMG_NAME) > /dev/null
	@echo "[img] Creating fat16 file system: OK"
	@dd if=$(BUILDDIR)/mbr.bin of=$(IMG_NAME) bs=1 count=3 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1
	@dd if=$(BUILDDIR)/mbr.bin of=$(IMG_NAME) skip=62 seek=62 bs=1 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1
	@echo "[img] Writing MBR: OK"
	@dd if=$(BUILDDIR)/bootloader.bin of=$(IMG_NAME) bs=512 seek=1 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1
	@echo "[img] Writing second bootloader: OK"
	@echo "[img] Creating disk image: OK"

# Run qemu

run: build img
	@echo "[run] Running in emulator..."
	@sudo qemu-system-x86_64 -drive file=./$(IMG_NAME),format=raw,if=virtio
