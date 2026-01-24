.section .text

.intel_syntax noprefix
.code32

/* Debug exception */
.global isr_debug_exception_stub
.type isr_debug_exception_stub, @function
isr_debug_exception_stub:
    cli

    mov eax, [esp + 8]
    and eax, 0xFFFFFEFF
    mov [esp + 8], eax

    pusha
    push ds
    push es
    push fs
    push gs

    call isr_debug_exception

    pop gs
    pop fs
    pop es
    pop ds
    popa

    sti
    iretd


/* Breakpoint */
.global isr_breakpoint_stub
.type isr_breakpoint_stub, @function
isr_breakpoint_stub:
    pusha

    push ds
    push es
    push fs
    push gs

    call isr_breakpoint

    pop gs
    pop fs
    pop es
    pop ds

    popa
    iretd

/* Common stub */
.global isr_common_stub
.type isr_common_stub, @function
isr_common_stub:
    call isr_common_handler


.intel_syntax noprefix
.code32

/* Divide Error (0x00) */
.global isr0_stub
.type isr0_stub, @function
isr0_stub:
    push 0
    push 0
    jmp isr_common_stub

/* Non-Maskable Interrupt (0x02) */
.global isr2_stub
.type isr2_stub, @function
isr2_stub:
    push 0
    push 2
    jmp isr_common_stub

/* Overflow (0x04) */
.global isr4_stub
.type isr4_stub, @function
isr4_stub:
    push 0
    push 4
    jmp isr_common_stub

/* BOUND Range Exceeded (0x05) */
.global isr5_stub
.type isr5_stub, @function
isr5_stub:
    push 0
    push 5
    jmp isr_common_stub

/* Invalid Opcode (0x06) */
.global isr6_stub
.type isr6_stub, @function
isr6_stub:
    push 0
    push 6
    jmp isr_common_stub

/* Device Not Available (0x07) */
.global isr7_stub
.type isr7_stub, @function
isr7_stub:
    push 0
    push 7
    jmp isr_common_stub

/* Double Fault (0x08) */
.global isr8_stub
.type isr8_stub, @function
isr8_stub:
    push 0
    push 8
    jmp isr_common_stub

/* Coprocessor Segment Overrun (0x09) */
.global isr9_stub
.type isr9_stub, @function
isr9_stub:
    push 0
    push 9
    jmp isr_common_stub

/* Invalid TSS (0x10) */
.global isr10_stub
.type isr10_stub, @function
isr10_stub:
    push 0
    push 10
    jmp isr_common_stub

/* Segment Not Present (0x11) */
.global isr11_stub
.type isr11_stub, @function
isr11_stub:
    push 0
    push 11
    jmp isr_common_stub

/* Stack-Segment Fault (0x12) */
.global isr12_stub
.type isr12_stub, @function
isr12_stub:
    push 0
    push 12
    jmp isr_common_stub

/* General Protection Fault (0x13) */
.global isr13_stub
.type isr13_stub, @function
isr13_stub:
    push 0
    push 13
    jmp isr_common_stub

/* Page Fault (0x14) */
.global isr14_stub
.type isr14_stub, @function
isr14_stub:
    push 0
    push 14
    jmp isr_common_stub

/* Reserved (0x15) */
.global isr15_stub
.type isr15_stub, @function
isr15_stub:
    push 0
    push 15
    jmp isr_common_stub

/* x87 Floating-Point Error (0x16) */
.global isr16_stub
.type isr16_stub, @function
isr16_stub:
    push 0
    push 16
    jmp isr_common_stub

/* Alignment Check (0x17) */
.global isr17_stub
.type isr17_stub, @function
isr17_stub:
    push 0
    push 17
    jmp isr_common_stub

/* Machine Check (0x18) */
.global isr18_stub
.type isr18_stub, @function
isr18_stub:
    push 0
    push 18
    jmp isr_common_stub

/* SIMD Floating-Point Exception (0x19) */
.global isr19_stub
.type isr19_stub, @function
isr19_stub:
    push 0
    push 19
    jmp isr_common_stub

/* Virtualization Exception (0x20) */
.global isr20_stub
.type isr20_stub, @function
isr20_stub:
    push 0
    push 20
    jmp isr_common_stub

/* Control Protection Exception (0x21) */
.global isr21_stub
.type isr21_stub, @function
isr21_stub:
    push 0
    push 21
    jmp isr_common_stub

/* Reserved (0x22–0x31) */
.global isr22_stub
.type isr22_stub, @function
isr22_stub:
    push 0
    push 22
    jmp isr_common_stub

.global isr23_stub
.type isr23_stub, @function
isr23_stub:
    push 0
    push 23
    jmp isr_common_stub

.global isr24_stub
.type isr24_stub, @function
isr24_stub:
    push 0
    push 24
    jmp isr_common_stub

.global isr25_stub
.type isr25_stub, @function
isr25_stub:
    push 0
    push 25
    jmp isr_common_stub

.global isr26_stub
.type isr26_stub, @function
isr26_stub:
    push 0
    push 26
    jmp isr_common_stub

.global isr27_stub
.type isr27_stub, @function
isr27_stub:
    push 0
    push 27
    jmp isr_common_stub

.global isr28_stub
.type isr28_stub, @function
isr28_stub:
    push 0
    push 28
    jmp isr_common_stub

.global isr29_stub
.type isr29_stub, @function
isr29_stub:
    push 0
    push 29
    jmp isr_common_stub

.global isr30_stub
.type isr30_stub, @function
isr30_stub:
    push 0
    push 30
    jmp isr_common_stub

.global isr31_stub
.type isr31_stub, @function
isr31_stub:
    push 0
    push 31
    jmp isr_common_stub
