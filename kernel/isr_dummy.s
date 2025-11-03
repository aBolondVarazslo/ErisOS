/* A simple dummy ISR for testing */

.section .text
.global isr_dummy
.type isr_dummy, @function

isr_dummy:
    iret

.size isr_dummy, . - isr_dummy