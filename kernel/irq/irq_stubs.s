.section .text

.intel_syntax noprefix
.code32

/* IRQ0 – Timer (0x20) */
.global irq0_stub
.type irq0_stub, @function
irq0_stub:
    mov byte ptr [0xB8000], '!'
    mov byte ptr [0xB8001], 0x07
    hlt
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x20
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ1 – Keyboard (0x21) */
.global irq1_stub
.type irq1_stub, @function
irq1_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x21
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ2 – Cascade (0x22) */
.global irq2_stub
.type irq2_stub, @function
irq2_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x22
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ3 – COM2 / COM4 (0x23) */
.global irq3_stub
.type irq3_stub, @function
irq3_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x23
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ4 – COM1 / COM3 (0x24) */
.global irq4_stub
.type irq4_stub, @function
irq4_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x24
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ5 – LPT2 / Audio / etc. (0x25) */
.global irq5_stub
.type irq5_stub, @function
irq5_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x25
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ6 – Floppy (0x26) */
.global irq6_stub
.type irq6_stub, @function
irq6_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x26
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ7 – LPT1 / Spurious (0x27) */
.global irq7_stub
.type irq7_stub, @function
irq7_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x27
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ8 – RTC (0x28) */
.global irq8_stub
.type irq8_stub, @function
irq8_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x28
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ9 – Unassigned / Redirected (0x29) */
.global irq9_stub
.type irq9_stub, @function
irq9_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x29
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ10 – Unassigned (0x2A) */
.global irq10_stub
.type irq10_stub, @function
irq10_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x2A
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ11 – Unassigned (0x2B) */
.global irq11_stub
.type irq11_stub, @function
irq11_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x2B
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ12 – PS/2 Mouse (0x2C) */
.global irq12_stub
.type irq12_stub, @function
irq12_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x2C
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ13 – FPU exception (0x2D) */
.global irq13_stub
.type irq13_stub, @function
irq13_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x2D
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ14 – ATA primary (0x2E) */
.global irq14_stub
.type irq14_stub, @function
irq14_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x2E
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret

/* IRQ15 – ATA secondary (0x2F) */
.global irq15_stub
.type irq15_stub, @function
irq15_stub:
    pushad
	push ds
    push es
    push fs
    push gs

    push 0x2F
    call irq_common_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
	popad
    iret