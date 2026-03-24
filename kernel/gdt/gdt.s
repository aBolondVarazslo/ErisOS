.section .text

.intel_syntax noprefix
.code32

.global gdt_init
.type gdt_init, @function
gdt_init:
    /* NULL descriptor (index 0) */
    mov dword ptr [gdt + 0*8], 0
    mov dword ptr [gdt + 0*8 + 4], 0

    /* Kernel code descriptor (index 1, selector 0x08) */
    mov word ptr  [gdt + 1*8],     0xFFFF     /* limit low */
    mov word ptr  [gdt + 1*8 + 2], 0x0000     /* base low */
    mov byte ptr  [gdt + 1*8 + 4], 0x00       /* base middle */
    mov byte ptr  [gdt + 1*8 + 5], 0x9A       /* access: present, ring0, code, readable, executed */
    mov byte ptr  [gdt + 1*8 + 6], 0xCF       /* granularity + limit high */
    mov byte ptr  [gdt + 1*8 + 7], 0x00       /* base high */

    /* Kernel data descriptor (index 2, selector 0x10) */
    mov word ptr  [gdt + 2*8],     0xFFFF     /* limit low */
    mov word ptr  [gdt + 2*8 + 2], 0x0000     /* base low */
    mov byte ptr  [gdt + 2*8 + 4], 0x00       /* base middle */
    mov byte ptr  [gdt + 2*8 + 5], 0x92       /* access: present, ring0, data, writable */
    mov byte ptr  [gdt + 2*8 + 6], 0xCF       /* granularity + limit high */
    mov byte ptr  [gdt + 2*8 + 7], 0x00       /* base high */

    /* Load GDT */
    lgdt [gdtr]

    mov byte ptr [0xB8000], 'G'
    mov byte ptr [0xB8001], 0x0F

    mov byte ptr [0xB8002], 'D'
    mov byte ptr [0xB8003], 0x0F

    mov byte ptr [0xB8004], 'T'
    mov byte ptr [0xB8005], 0x0F

    mov byte ptr [0xB8006], ' '
    mov byte ptr [0xB8007], 0x0F

    mov byte ptr [0xB8008], 'O'
    mov byte ptr [0xB8009], 0x0F

    mov byte ptr [0xB800A], 'K'
    mov byte ptr [0xB800B], 0x0F

    /* Far jump to reload CS with selector 0x08 */
    jmp 0x08:.flush_cs

.flush_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret

.section .data
.align 8
gdt:
    /* 3 entries * 8 bytes */
    .skip 24

gdtr:
    .word 23 /* limit = 24 - 1 */
    .long gdt /* base */