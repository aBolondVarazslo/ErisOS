/* SOURCE: https://wiki.osdev.org/Bare_Bones#Booting_the_Operating_System */
/* Code has simply been translated from AT&T syntax to Intel for simplicity */

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

/* Temporary page directory */
.section .boot.data, "aw", @progbits
.balign 4096
boot_page_directory:
    .skip 4096

/* Stack */
.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:

/* Code */
/* Switch syntax before instructions */
.intel_syntax noprefix
.code32

/* Runs with paging off */
.section .boot.text, "ax", @progbits
.global _start
.type _start, @function
_start:
    mov eax, offset boot_page_directory

    mov dword ptr [eax], 0x83
    mov dword ptr [eax + 0xC00], 0x83

    mov ecx, cr4
    or ecx, 0x10
    mov cr4, ecx

    mov cr3, eax

    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    mov ecx, offset higher_half
    jmp ecx

.size _start, . - _start

.section .text
higher_half:
    mov esp, offset stack_top
    and esp, 0xFFFFFFF0

    push ebx

    call kernel_main

    cli
1:  hlt
    jmp 1b