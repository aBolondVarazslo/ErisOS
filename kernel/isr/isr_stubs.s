.section .text

.intel_syntax noprefix
.code32

/* Debug Exception (0x01) */
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

/* Breakpoint (0x03) */
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

/* Divide Error (0x00) */
.global isr0_stub
.type isr0_stub, @function
isr0_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 0
    call isr_common_handler

/* Non-Maskable Interrupt (0x02) */
.global isr2_stub
.type isr2_stub, @function
isr2_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 2
    call isr_common_handler

/* Overflow (0x04) */
.global isr4_stub
.type isr4_stub, @function
isr4_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 4
    call isr_common_handler

/* BOUND Range Exceeded (0x05) */
.global isr5_stub
.type isr5_stub, @function
isr5_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 5
    call isr_common_handler

/* Invalid Opcode (0x06) */
.global isr6_stub
.type isr6_stub, @function
isr6_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 6
    call isr_common_handler

/* Device Not Available (0x07) */
.global isr7_stub
.type isr7_stub, @function
isr7_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 7
    call isr_common_handler

/* Double Fault (0x08) */
.global isr8_stub
.type isr8_stub, @function
isr8_stub:
    lea eax, [esp + 4]
    push eax
    push 8
    call isr_common_handler

/* Coprocessor Segment Overrun (0x09) */
.global isr9_stub
.type isr9_stub, @function
isr9_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 9
    call isr_common_handler

/* Invalid TSS (0x0A) */
.global isr10_stub
.type isr10_stub, @function
isr10_stub:
    lea eax, [esp + 4]
    push eax
    push 10
    call isr_common_handler

/* Segment Not Present (0x0B) */
.global isr11_stub
.type isr11_stub, @function
isr11_stub:
    lea eax, [esp + 4]
    push eax
    push 11
    call isr_common_handler

/* Stack-Segment Fault (0x0C) */
.global isr12_stub
.type isr12_stub, @function
isr12_stub:
    lea eax, [esp + 4]
    push eax
    push 12
    call isr_common_handler

/* General Protection Fault (0x0D) */
.global isr13_stub
.type isr13_stub, @function
isr13_stub:
    lea eax, [esp + 4]
    push eax
    push 13
    call isr_common_handler

/* Page Fault (0x0E) */
.global isr14_stub
.type isr14_stub, @function
isr14_stub:
    lea eax, [esp + 4]
    push eax
    push 14
    call isr_common_handler

/* Reserved (0x0F) */
.global isr15_stub
.type isr15_stub, @function
isr15_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 15
    call isr_common_handler

/* x87 Floating-Point Error (0x10) */
.global isr16_stub
.type isr16_stub, @function
isr16_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 16
    call isr_common_handler

/* Alignment Check (0x11) */
.global isr17_stub
.type isr17_stub, @function
isr17_stub:
    lea eax, [esp + 4]
    push eax
    push 17
    call isr_common_handler

/* Machine Check (0x12) */
.global isr18_stub
.type isr18_stub, @function
isr18_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 18
    call isr_common_handler

/* SIMD Floating-Point Exception (0x13) */
.global isr19_stub
.type isr19_stub, @function
isr19_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 19
    call isr_common_handler

/* Virtualization Exception (0x14) */
.global isr20_stub
.type isr20_stub, @function
isr20_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 20
    call isr_common_handler

/* Control Protection Exception (0x15) */
.global isr21_stub
.type isr21_stub, @function
isr21_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 21
    call isr_common_handler

/* Reserved (0x16–0x1F) */
.global isr22_stub
.type isr22_stub, @function
isr22_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 22
    call isr_common_handler

.global isr23_stub
.type isr23_stub, @function
isr23_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 23
    call isr_common_handler

.global isr24_stub
.type isr24_stub, @function
isr24_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 24
    call isr_common_handler

.global isr25_stub
.type isr25_stub, @function
isr25_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 25
    call isr_common_handler

.global isr26_stub
.type isr26_stub, @function
isr26_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 26
    call isr_common_handler

.global isr27_stub
.type isr27_stub, @function
isr27_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 27
    call isr_common_handler

.global isr28_stub
.type isr28_stub, @function
isr28_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 28
    call isr_common_handler

.global isr29_stub
.type isr29_stub, @function
isr29_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 29
    call isr_common_handler

.global isr30_stub
.type isr30_stub, @function
isr30_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 30
    call isr_common_handler

.global isr31_stub
.type isr31_stub, @function
isr31_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 31
    call isr_common_handler