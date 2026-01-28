#include "irq.h"

/* Array of IRQ assembly stubs */
void (*irq_stubs[16])(void) = {
    irq0_stub,  irq1_stub,  irq2_stub,  irq3_stub,
    irq4_stub,  irq5_stub,  irq6_stub,  irq7_stub,
    irq8_stub,  irq9_stub,  irq10_stub, irq11_stub,
    irq12_stub, irq13_stub, irq14_stub, irq15_stub
};
