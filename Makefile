BUILD_DIR = build
BUILD_BOOTLOADER_DIR = $(BUILD_DIR)/bootloader
BUILD_KERNEL_DIR = $(BUILD_DIR)/kernel
BUILD_APPS_DIR = $(BUILD_KERNEL_DIR)/apps
BUILD_CORE_DIR = $(BUILD_KERNEL_DIR)/core
BUILD_CPU_DIR = $(BUILD_KERNEL_DIR)/cpu
BUILD_DEBUGGING_DIR = $(BUILD_KERNEL_DIR)/debugging
BUILD_DRIVERS_DIR = $(BUILD_KERNEL_DIR)/drivers
BUILD_LIB_DIR = $(BUILD_KERNEL_DIR)/lib


SRC_BOOTLOADER_DIR = src/bootloader
SRC_GRUB_DIR = src/grub
SRC_KERNEL_DIR = src/kernel
SRC_APPS_DIR = $(SRC_KERNEL_DIR)/apps
SRC_CORE_DIR = $(SRC_KERNEL_DIR)/core
SRC_CPU_DIR = $(SRC_KERNEL_DIR)/cpu
SRC_DEBUGGING_DIR = $(SRC_KERNEL_DIR)/debugging
SRC_DRIVERS_DIR = $(SRC_KERNEL_DIR)/drivers
SRC_LIB_DIR = $(SRC_KERNEL_DIR)/lib


all:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_BOOTLOADER_DIR)
	mkdir -p $(BUILD_APPS_DIR)/shell
	mkdir -p $(BUILD_CORE_DIR)
	mkdir -p $(BUILD_CPU_DIR)/gdt
	mkdir -p $(BUILD_CPU_DIR)/idt
	mkdir -p $(BUILD_CPU_DIR)/isr
	mkdir -p $(BUILD_CPU_DIR)/irq
	mkdir -p $(BUILD_DEBUGGING_DIR)
	mkdir -p $(BUILD_DRIVERS_DIR)/pic
	mkdir -p $(BUILD_DRIVERS_DIR)/pit
	mkdir -p $(BUILD_DRIVERS_DIR)/ps2
	mkdir -p $(BUILD_DRIVERS_DIR)/io
	mkdir -p $(BUILD_LIB_DIR)

	# Assemble the boot file and stubs
	i686-elf-as $(SRC_BOOTLOADER_DIR)/boot.s -o $(BUILD_BOOTLOADER_DIR)/boot.o
	i686-elf-as $(SRC_CPU_DIR)/gdt/gdt.s -o $(BUILD_CPU_DIR)/gdt/gdt.o
	i686-elf-as $(SRC_CPU_DIR)/isr/isr_stubs.s -o $(BUILD_CPU_DIR)/isr/isr_stubs.o
	i686-elf-as $(SRC_CPU_DIR)/irq/irq_stubs.s -o $(BUILD_CPU_DIR)/irq/irq_stubs.o

	# Compile kernel source files
	i686-elf-gcc -c $(SRC_CORE_DIR)/kernel.c -o $(BUILD_CORE_DIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_LIB_DIR)/terminal.c -o $(BUILD_LIB_DIR)/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_DEBUGGING_DIR)/debugging.c -o $(BUILD_DEBUGGING_DIR)/debugging.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_CPU_DIR)/idt/idt.c -o $(BUILD_CPU_DIR)/idt/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_CPU_DIR)/isr/isr.c -o $(BUILD_CPU_DIR)/isr/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_CPU_DIR)/irq/irq.c -o $(BUILD_CPU_DIR)/irq/irq.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_DRIVERS_DIR)/pic/pic.c -o $(BUILD_DRIVERS_DIR)/pic/pic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_DRIVERS_DIR)/pit/pit.c -o $(BUILD_DRIVERS_DIR)/pit/pit.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_DRIVERS_DIR)/ps2/ps2.c -o $(BUILD_DRIVERS_DIR)/ps2/ps2.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_DRIVERS_DIR)/io/io.c -o $(BUILD_DRIVERS_DIR)/io/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(SRC_APPS_DIR)/shell/shell.c -o $(BUILD_APPS_DIR)/shell/shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	# Link kernel
	i686-elf-gcc -T linker.ld -o build/ErisOS.bin -ffreestanding -O2 -nostdlib \
		$(BUILD_BOOTLOADER_DIR)/boot.o \
		$(BUILD_CORE_DIR)/kernel.o \
		$(BUILD_LIB_DIR)/terminal.o \
		$(BUILD_DEBUGGING_DIR)/debugging.o \
		$(BUILD_CPU_DIR)/gdt/gdt.o \
		$(BUILD_CPU_DIR)/idt/idt.o \
		$(BUILD_CPU_DIR)/isr/isr.o \
		$(BUILD_CPU_DIR)/isr/isr_stubs.o \
		$(BUILD_CPU_DIR)/irq/irq.o \
		$(BUILD_CPU_DIR)/irq/irq_stubs.o \
		$(BUILD_DRIVERS_DIR)/pic/pic.o \
		$(BUILD_DRIVERS_DIR)/pit/pit.o \
		$(BUILD_DRIVERS_DIR)/ps2/ps2.o \
		$(BUILD_DRIVERS_DIR)/io/io.o \
		$(BUILD_APPS_DIR)/shell/shell.o \
		-lgcc

	# Validate multiboot
	./multiboot-checker.sh

	# Create ISO
	mkdir -p isodir/boot/grub
	cp $(BUILD_DIR)/ErisOS.bin isodir/boot/ErisOS.bin
	cp $(SRC_GRUB_DIR)/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ErisOS.iso isodir

clean:
	rm -rf build/
	rm -rf isodir/
	rm -f ErisOS.iso
