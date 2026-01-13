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

.global isr_common_stub
.type isr_common_stub, @function
isr_common_stub:
    call isr_common_handler