all:
	rm -rf build/
	mkdir -p build/bootloader
	mkdir -p build/kernel/gdt
	mkdir -p build/kernel/idt
	mkdir -p build/kernel/isr
	mkdir -p build/kernel/irq
	mkdir -p build/kernel/debugging
	mkdir -p build/kernel/pic
	mkdir -p build/kernel/pit
	mkdir -p build/kernel/io

	# Assemble the boot file and stubs
	i686-elf-as bootloader/boot.s -o build/bootloader/boot.o
	i686-elf-as kernel/isr/isr_stubs.s -o build/kernel/isr/isr_stubs.o
	i686-elf-as kernel/irq/irq_stubs.s -o build/kernel/irq/irq_stubs.o

	# Compile kernel source files
	i686-elf-gcc -c kernel/kernel.c -o build/kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/terminal.c -o build/kernel/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/debugging/debugging.c -o build/kernel/debugging/debugging.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/gdt/gdt.c -o build/kernel/gdt/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/idt/idt.c -o build/kernel/idt/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/isr/isr.c -o build/kernel/isr/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/irq/irq.c -o build/kernel/irq/irq.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/pic/pic.c -o build/kernel/pic/pic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/pit/pit.c -o build/kernel/pit/pit.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/io/io.c -o build/kernel/io/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	# Link kernel
	i686-elf-gcc -T linker.ld -o build/ErisOS.bin -ffreestanding -O2 -nostdlib \
		build/bootloader/boot.o \
		build/kernel/kernel.o \
		build/kernel/terminal.o \
		build/kernel/debugging/debugging.o \
		build/kernel/gdt/gdt.o \
		build/kernel/idt/idt.o \
		build/kernel/isr/isr.o \
		build/kernel/isr/isr_stubs.o \
		build/kernel/irq/irq.o \
		build/kernel/irq/irq_stubs.o \
		build/kernel/pic/pic.o \
		build/kernel/pit/pit.o \
		build/kernel/io/io.o \
		-lgcc

	# Validate multiboot
	./multiboot-checker.sh

	# Create ISO
	mkdir -p isodir/boot/grub
	cp build/ErisOS.bin isodir/boot/ErisOS.bin
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ErisOS.iso isodir

clean:
	rm -rf build/
	rm -rf isodir/
	rm -f ErisOS.iso
