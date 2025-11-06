.section .text


/* Divide error */

.global isr_divide_error_stub
.type isr_divide_error_stub, @function

isr_divide_error_stub:      /* Temporary */
    cli
    pusha

    push %ds
    push %es
    push %fs
    push %gs

    call isr_divide_error

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
    cli
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
    sti
    iret