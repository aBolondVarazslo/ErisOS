.section .text


/* Debug exception */
.global isr_debug_exception_stub
.type isr_debug_exception_stub, @function
isr_debug_exception_stub:
    cli

    movl 8(%esp), %eax
    andl $0xFFFFFEFF, %eax
    movl %eax, 8(%esp)

    pusha
    push %ds
    push %es
    push %fs
    push %gs

    call isr_debug_exception

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    sti
    iret


/* Breakpoint */
.global isr_breakpoint_stub
.type isr_breakpoint_stub, @function
isr_breakpoint_stub:
    pusha

    push %ds
    push %es
    push %fs
    push %gs

    call isr_breakpoint

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa
    iret

.global isr_common_stub
.type isr_common_stub, @function
isr_common_stub:
    call isr_common_handler