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


/* Divide error */
.global isr_divide_error_stub
.type isr_divide_error_stub, @function
isr_divide_error_stub:
    call isr_divide_error


/* NMI */
.global isr_nmi_stub
.type isr_nmi_stub, @function
isr_nmi_stub:
    call isr_nmi


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


/* Overflow */
.global isr_overflow_stub
.type isr_overflow_stub, @function
isr_overflow_stub:
    call isr_overflow


/* Bound range exceeded */
.global isr_bound_range_exceeded_stub
.type isr_bound_range_exceeded_stub, @function
isr_bound_range_exceeded_stub:
    call isr_bound_range_exceeded