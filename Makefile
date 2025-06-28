QEMU = qemu-system-i386
BL = bootloader/bootloader.asm
BBL = build/bootloader
S2 = bootloader/stage2.asm
IMG = build/erisos.img
GCC = i386-elf-gcc
LD = i386-elf-ld

all:
	mkdir -p build/bootloader
	mkdir build/kernel
	nasm -f bin ${BL} -o ${BBL}/bootloader.bin
	nasm -f bin ${S2} -o ${BBL}/stage2.bin
	cat ${BBL}/bootloader.bin ${BBL}/stage2.bin > ${IMG}
	${GCC} -ffreestanding -m32 -c kernel/kernel.c -o build/kernel/kernel.o

run: all
	${QEMU} -drive format=raw,file=${IMG},index=0,if=floppy

clean:
	rm -rf build
