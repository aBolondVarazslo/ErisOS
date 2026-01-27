#include "pic.h"
#include "../io/io.h"
#include "../terminal.h"

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

    /* Unmask all IRQs */
    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);

    terminal_writeString("PIC Remapped", STATUS_SUCCESS);
}

void PIC_set_mask(uint8_t mask1, uint8_t mask2) {
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);

    terminal_writeString("PIC masked", STATUS_SUCCESS);
}