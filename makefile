BIN_DIR   = bin
BIN       = $(BIN_DIR)/kernel.bin
ISO       = image.iso
ISO_ROOT  = iso_root
SRC_DIR   = source
SOURCES   = $(SRC_DIR)/main.c \
            $(SRC_DIR)/LimineRequests.c \
            $(SRC_DIR)/memory.c
CFILES    = $(filter %.c,$(SOURCES))
ASFILES   = $(filter %.S,$(SOURCES))
NASMFILES = $(filter %.asm,$(SOURCES))
OBJ_DIR   = objects
OBJECTS   = $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:.c=.c.o)) \
                $(notdir $(ASFILES:.S=.S.o)) \
                $(notdir $(NASMFILES:.asm=.asm.o)))
CC        = gcc
CFLAGS    = -Wall \
            -Wextra \
            -Werror \
            -Wpedantic \
            -std=gnu23 \
            -ffreestanding \
            -fno-stack-protector \
            -fno-stack-check \
            -fno-PIC \
            -m64 \
            -march=x86-64 \
            -mno-80387 \
            -mno-mmx \
            -mno-sse \
            -mno-sse2 \
            -mno-red-zone \
            -I src \
            -DLIMINE_API_REVISION=3 \
            -MMD \
            -MP \
            -mcmodel=kernel
LDFLAGS   = -Wl,-m,elf_x86_64 \
            -Wl,--build-id=none \
            -nostdlib \
            -static \
            -z max-page-size=0x1000 \
            -T linker.ld
NASMFLAGS = -Wall -f elf64

.PHONY: all clean run
all: $(ISO)


$(BIN_DIR) $(OBJ_DIR) $(ISO_ROOT):
	mkdir $@

$(BIN): linker.ld $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.S.o: $(SRC_DIR)/%.S | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.asm.o: $(SRC_DIR)/%.asm | $(OBJ_DIR)
	nasm $(NASMFLAGS) $< -o $@

$(ISO): $(BIN) | $(ISO_ROOT)
	mkdir -p $(ISO_ROOT)/boot/limine
	cp -v $(BIN) $(ISO_ROOT)/boot/
	cp -v limine.conf limine/limine-bios.sys limine/limine-bios-cd.bin \
		limine/limine-uefi-cd.bin $(ISO_ROOT)/boot/limine/
	mkdir -p iso_root/EFI/BOOT
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
        -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        iso_root -o $@
	./limine/limine bios-install $@

run: $(ISO)
	qemu-system-x86_64 -hda $(ISO)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(ISO) $(ISO_ROOT)

