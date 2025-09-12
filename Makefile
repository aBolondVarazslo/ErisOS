all:
	rm -rf build/
	mkdir -p build/bootloader
	mkdir -p build/kernel

	i686-elf-as bootloader/boot.s -o build/bootloader/boot.o
	i686-elf-gcc -c kernel/kernel.c -o build/kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o build/ErisOS.bin -ffreestanding -O2 -nostdlib build/bootloader/boot.o build/kernel/kernel.o -lgcc
	./multiboot-checker.sh

	mkdir -p isodir/boot/grub
	cp build/ErisOS.bin isodir/boot/ErisOS.bin
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ErisOS.iso isodir

	rm -rf build/	

run:
	qemu-system-i386 -cdrom ErisOS.iso --nographic

clean:
	rm -rf build/
	rm -rf isodir/
	rm ErisOS.iso
