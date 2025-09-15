all:
	rm -rf build/
	mkdir -p build/bootloader
	mkdir -p build/kernel

	# Assemble the bootloader
	i686-elf-as bootloader/boot.s -o build/bootloader/boot.o

	# Compile kernel source files
	i686-elf-gcc -c kernel/kernel.c -o build/kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/terminal.c -o build/kernel/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	# Link kernel
	i686-elf-gcc -T linker.ld -o build/ErisOS.bin -ffreestanding -O2 -nostdlib \
		build/bootloader/boot.o \
		build/kernel/kernel.o \
		build/kernel/terminal.o \
		-lgcc

	# Validate multiboot
	./multiboot-checker.sh

	# Create ISO
	mkdir -p isodir/boot/grub
	cp build/ErisOS.bin isodir/boot/ErisOS.bin
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ErisOS.iso isodir

	# Clean up intermediate files
	rm -rf build/

run:
	qemu-system-i386 -cdrom ErisOS.iso --nographic

clean:
	rm -rf build/
	rm -rf isodir/
	rm -f ErisOS.iso
