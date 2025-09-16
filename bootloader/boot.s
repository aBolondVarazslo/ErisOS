/* SOURCE: https://wiki.osdev.org/Bare_Bones#Booting_the_Operating_System */

/* Declare constants for the multiboot header. */
.set ALIGN,	1<<0		/* align loaded modules on page boundaries */
.set MEMINFO,	1<<1		/* provides memory map */
.set FLAGS,	ALIGN | MEMINFO	/* this is the Multiboot 'flag' field */
.set MAGIC,	0x1BADB002	/* 'magic number' lets bootloader find the header */
.set CHECKSUM,	-(MAGIC + FLAGS)/* checksum of the above, to prove in multiboot */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16

stack_bottom:
.skip 16384 # 16 KiB

stack_top:

.section .text
.global _start
.type _start, @function
_start:

	mov $stack_top, %esp

	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
