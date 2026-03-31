#include "irq.h"
#include "../../drivers/pic/pic.h"
#include "../../lib/terminal.h"

void irq_common_handler(uint32_t int_no) {
    uint32_t irq = int_no - 0x20; /* Convert vector number to IRQ number */

    if (irq != 0) {
        terminal_writeString("IRQ ", STATUS_DEBUG);
        terminal_writeHex(irq);
        terminal_writeString(" fired\n", STATUS_DEBUG);
    }

    /* Send End Of Interrupt */
    if (irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}

/* Array of IRQ assembly stubs */
void (*irq_stubs[16])(void) = {irq0_stub,  irq1_stub,  irq2_stub,  irq3_stub, irq4_stub,  irq5_stub,
                               irq6_stub,  irq7_stub,  irq8_stub,  irq9_stub, irq10_stub, irq11_stub,
                               irq12_stub, irq13_stub, irq14_stub, irq15_stub};
