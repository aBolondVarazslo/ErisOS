.section .text


.global isr_divide_error_stub
.type isr_divide_error_stub, @function

isr_divide_error_stub:
    cli
    iret




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
    .size isr_breakpoint_stub, . - isr_breakpoint_stub
