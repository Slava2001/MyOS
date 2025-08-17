.PHONY: build img run help default

BUILDDIR = build
IMG_NAME = os.img
IMG_SIZE_MB = 16 # Range: 16Mb - 2G
SECOND_BOOTLOADER_SIZE_SECTORS = 20
CC = bcc
CFLAGS = -ansi -0 -f -W
AS = nasm
ASFLAGS = -w+error
LD = ld86
LDFLAGS = -d
help:
	@echo "Available commands:"
	@echo "  make clean   - remove compile artifacts"
	@echo "  make build   - compile the project"
	@echo "  make img     - create a disk image"
	@echo "  make run     - run the OS in qemu"

clean:
	@rm -rf $(BUILDDIR)

build: mbr.bin bootloader.bin kernel.bin
	@echo "[build] Compiling the project: OK"

INCLUDE_DIRS = include
INCLUDE_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))

LIB_SRC = $(wildcard src/lib/*)
LIB_OBJ = $(LIB_SRC:=.o)

SRT0_SRC = src/crt0.asm
SRT0_OBJ = $(SRT0_SRC:=.o)

MBR_SRC = ./src/main_boot_record.asm
mbr.bin: $(MBR_SRC)
	@echo "[build] Compile $(@F)"
	@mkdir -p $(BUILDDIR)/$(@D)
	    @$(AS) $(INCLUDE_FLAGS) $(ASFLAGS) -f bin $< -o $(BUILDDIR)/$@

BOOTLOADER_SRC = $(wildcard src/bootloader/*)
bootloader.bin: $(SRT0_OBJ) $(BOOTLOADER_SRC:=.o) $(LIB_OBJ)
	@echo "[build] Compile $(@F)"
	    @$(LD) $(LDFLAGS) $(addprefix $(BUILDDIR)/,$+) -o $(BUILDDIR)/$@
	@if [ "$$(stat -c %s $(BUILDDIR)/$@)" -gt "$$((512 * $(SECOND_BOOTLOADER_SIZE_SECTORS)))" ]; then \
         exit 1; \
     fi

KERNEL_SRC = $(wildcard src/kernel/*)
kernel.bin: $(SRT0_OBJ) $(KERNEL_SRC:=.o) $(LIB_OBJ)
	@echo "[build] Compile $(@F)"
	    @$(LD) $(LDFLAGS) $(addprefix $(BUILDDIR)/,$+) -o $(BUILDDIR)/$@

%.c.o :: %.c
	@echo "[build] Compile $(@F)"
	@mkdir -p $(BUILDDIR)/$(@D)
	    @$(CC) -c $(INCLUDE_FLAGS) $(CFLAGS) $< -o $(BUILDDIR)/$@

%.asm.o :: %.asm
	@echo "[build] Compile $(@F)"
	@mkdir -p $(BUILDDIR)/$(@D)
	    @$(AS) $(INCLUDE_FLAGS) $(ASFLAGS) -f as86 $< -o $(BUILDDIR)/$@

img: build
	@rm -f $(IMG_NAME)
	@echo "[img] Remove old image: OK"
	@dd if=/dev/zero of=$(IMG_NAME) bs=1MiB count=$(IMG_SIZE_MB) > /dev/null 2>&1
	@echo "[img] Creating empty disk image: OK"
	@mkfs.fat -D 0 -n "LUNAR OS" -F 16 -R $(SECOND_BOOTLOADER_SIZE_SECTORS) $(IMG_NAME) > /dev/null
	@echo "[img] Creating fat16 file system: OK"
	@dd if=$(BUILDDIR)/mbr.bin of=$(IMG_NAME) bs=1 count=3 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1
	@dd if=$(BUILDDIR)/mbr.bin of=$(IMG_NAME) skip=62 seek=62 bs=1 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1
	@echo "[img] Writing MBR: OK"
	@dd if=$(BUILDDIR)/bootloader.bin of=$(IMG_NAME) bs=512 seek=1 conv=notrunc iflag=skip_bytes,count_bytes > /dev/null 2>&1
	@echo "[img] Writing second bootloader: OK"
	@set -e;                                                \
     temp_dir=$$(mktemp -d);                                \
     sudo mount -t msdos $(IMG_NAME) $$temp_dir -o loop;    \
     sudo cp -r ./src $$temp_dir;                           \
     sudo cp -r ./include $$temp_dir;                       \
     sudo cp $(BUILDDIR)/kernel.bin $$temp_dir;             \
     sudo cp ./3rdparty/HRY/LINES/LINES.COM $$temp_dir;     \
     sudo cp ./3rdparty/UTILITY/ASCII/ASCII.COM $$temp_dir; \
     sudo umount $(IMG_NAME);
	@echo "[img] Writing files: OK"
	@echo "[img] Creating disk image: OK"

run: img
	@echo "[run] Running in emulator..."
	@sudo qemu-system-x86_64 -drive file=./$(IMG_NAME),format=raw,if=virtio,media=cdrom
