# ErisOS

**ErisOS** is a small, bare-metal operating system for the x86 architecture, written in C. It is built as a learning project to explore low-level systems programming, bootloaders, and kernel development.

This kernel currently uses GRUB as its bootloader and prints basic status messages to the VGA text buffer in color. Over time, ErisOS will gain more features such as a scrolling terminal, input handling, and memory management.

---

## 🧰 Requirements

- **GCC** cross-compiler for i386 (`i386-elf-gcc`)
- **GNU Assembler** (for assembly files)
- **GRUB tools** (`grub-mkrescue`)
- **QEMU** (or any other emulator for testing)

You can install QEMU and GRUB using your distro's package manager.  
For the cross-compiler and assembler, see [OSDev Wiki: GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler).

## Build Instructions

To compile ErisOS and run it in QEMU:

```
make
make run
```

To clean the build:

```
make clean
```

To manually check if your kernel is multiboot-compliant:

```
./multiboot-checker.sh
```

---

## Current Features

- VGA text-mode output
- Coloured status messages (Green: successful, grey: in-progress tasks, red: failure, grey-on-blue: debug messages)
- Basic terminal_write and terminal_writeString functions

---

## Planned features

- Text wrapping and terminal scrolling
- Keyboard input
- Interrupt descriptor table (IDT)
- Programmable interrupt timer (PIT)
- Paging memory map parsing
- Custom shell
- Minimal filesystem support

---

## License

MIT License -- see `LICENSE` file for details

---

## Author

aBolondVarazslo
- Student software developer
- Building ErisOS as a personal learning project
- Passionate about low-level systems, compilers, and OS internals
- GitHub: [aBolondVarazslo](https://github.com/aBolondVarazslo)

---

## Credits & Resources

ErisOS uses resources from:
- [OSDev.org Wiki](https://wiki.osdev.org)
- [os-tutorial](https://github.com/cfenollosa/os-tutorial)
