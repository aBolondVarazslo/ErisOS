all:
	rm -rf build/
	mkdir -p build/bootloader
	mkdir -p build/kernel/core
	mkdir -p build/kernel/cpu/gdt
	mkdir -p build/kernel/cpu/idt
	mkdir -p build/kernel/cpu/isr
	mkdir -p build/kernel/cpu/irq
	mkdir -p build/kernel/debugging
	mkdir -p build/kernel/drivers/pic
	mkdir -p build/kernel/drivers/pit
	mkdir -p build/kernel/drivers/ps2
	mkdir -p build/kernel/drivers/io
	mkdir -p build/kernel/lib

	# Assemble the boot file and stubs
	i686-elf-as bootloader/boot.s -o build/bootloader/boot.o
	i686-elf-as kernel/cpu/gdt/gdt.s -o build/kernel/cpu/gdt/gdt.o
	i686-elf-as kernel/cpu/isr/isr_stubs.s -o build/kernel/cpu/isr/isr_stubs.o
	i686-elf-as kernel/cpu/irq/irq_stubs.s -o build/kernel/cpu/irq/irq_stubs.o

	# Compile kernel source files
	i686-elf-gcc -c kernel/core/kernel.c -o build/kernel/core/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/lib/terminal.c -o build/kernel/lib/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/debugging/debugging.c -o build/kernel/debugging/debugging.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	#i686-elf-gcc -c kernel/cpu/gdt/gdt.c -o build/kernel/cpu/gdt/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/cpu/idt/idt.c -o build/kernel/cpu/idt/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/cpu/isr/isr.c -o build/kernel/cpu/isr/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/cpu/irq/irq.c -o build/kernel/cpu/irq/irq.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/drivers/pic/pic.c -o build/kernel/drivers/pic/pic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/drivers/pit/pit.c -o build/kernel/drivers/pit/pit.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/drivers/ps2/ps2.c -o build/kernel/drivers/ps2/ps2.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/drivers/io/io.c -o build/kernel/drivers/io/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	# Link kernel
	i686-elf-gcc -T linker.ld -o build/ErisOS.bin -ffreestanding -O2 -nostdlib \
		build/bootloader/boot.o \
		build/kernel/core/kernel.o \
		build/kernel/lib/terminal.o \
		build/kernel/debugging/debugging.o \
		build/kernel/cpu/gdt/gdt.o \
		build/kernel/cpu/idt/idt.o \
		build/kernel/cpu/isr/isr.o \
		build/kernel/cpu/isr/isr_stubs.o \
		build/kernel/cpu/irq/irq.o \
		build/kernel/cpu/irq/irq_stubs.o \
		build/kernel/drivers/pic/pic.o \
		build/kernel/drivers/pit/pit.o \
		build/kernel/drivers/ps2/ps2.o \
		build/kernel/drivers/io/io.o \
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
