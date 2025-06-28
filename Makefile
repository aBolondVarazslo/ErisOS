QEMU = qemu-system-i386
BL = bootloader/bootloader.asm
IMG = build/erisos.img

all:
	mkdir -p build
	nasm -f bin ${BL} -o ${IMG}

run: all
	${QEMU} -drive format=raw,file=${IMG},index=0,if=floppy

clean:
	rm -rf build
