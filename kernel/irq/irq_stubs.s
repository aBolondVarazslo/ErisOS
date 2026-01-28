.section .text

.intel_syntax noprefix
.code32

/* IRQ0/System Timer (0x20) */
.global irq0_stub
.type irq0_stub, @function
irq0_stub:
    push 0              /* Fake error code */
    lea eax, [esp + 4]  /* Interrupt frame */
    push eax
    push 32             /* Vector number (0x20) */
    call irq_common_handler