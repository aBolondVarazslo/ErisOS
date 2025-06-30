all:
	rm -rf build/
	mkdir -p build/bootloader
	nasm -f bin bootloader/bootloader.asm -o build/bootloader/bootloader.bin
	nasm -f bin bootloader/stage2.asm -o build/bootloader/stage2.bin
	cat build/bootloader/bootloader.bin build/bootloader/stage2.bin > build/test.img

run:
	qemu-system-x86_64 -fda build/test.img --nographic
	rm -rf build/

clean:
	rm -rf build/
