#include "pic.h"
#include "../io/io.h"
#include "../../lib/terminal.h"

void PIC_remap(uint8_t offset1, uint8_t offset2) {
    /* Start initialisation in cascade mode, and tell PICs ICW4 will be present */
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    /* Set vector offsets */
    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();

    /* ICW3: Tell master/slave about cascade */
    outb(PIC1_DATA, 1 << CASCADE_IRQ);
    io_wait();
    outb(PIC2_DATA, CASCADE_IRQ);
    io_wait();

    /* ICW4: Set 8086/88 mode */
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    terminal_writeString("PIC Remapped\n", STATUS_SUCCESS);
}

void PIC_set_mask(uint8_t mask1, uint8_t mask2) {
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);

    terminal_writeString("PIC Masked\n", STATUS_SUCCESS);
}

/* Sends EOI (End Of Interrupt) to PIC */
void PIC_sendEOI(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}

/* Helper to read OCW3 from both PICs */
static uint16_t __pic__get__irq__reg(uint8_t ocw3) {
    outb(PIC1_COMMAND, ocw3);   /* Send command to master */
    outb(PIC2_COMMAND, ocw3);   /* Send command to slave */
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

/* Get the combined value of the cascaded PICs' IRR */
uint16_t pic_get_irr(void) {
    return __pic__get__irq__reg(PIC_READ_IRR);
}

/* Get the combined value of the cascaded PICs' ISR */
uint16_t pic_get_isr(void) {
    return __pic__get__irq__reg(PIC_READ_ISR);
}