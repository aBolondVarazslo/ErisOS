all:
	rm -rf build/
	mkdir -p build/bootloader
	mkdir -p build/kernel

	nasm -f bin bootloader/bootloader.asm -o build/bootloader/bootloader.bin
	nasm -f bin bootloader/stage2.asm -o build/bootloader/stage2.bin

	i686-elf-gcc -m32 -ffreestanding -nostdlib -fno-builtin -c kernel/kernel.c -o build/kernel/kernel.o
	i686-elf-ld -Ttext 0x100000 -o build/kernel/kernel.bin build/kernel/kernel.o --oformat binary
	
	cat build/bootloader/bootloader.bin build/bootloader/stage2.bin build/kernel/kernel.bin > build/test.img

run:
	qemu-system-x86_64 -fda build/test.img --nographic
	rm -rf build/

clean:
	rm -rf build/
