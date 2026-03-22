#include "pit.h"
#include "../io/io.h"
#include "../terminal.h"

#define PIT_CHANNEL0        0x40
#define PIT_COMMAND         0x43
#define PIT_BASE_FREQUENCY  1193182

void pit_init(uint32_t frequency) {
    /* Calculate divisor */
    uint32_t divisor = PIT_BASE_FREQUENCY / frequency;

    outb(PIT_COMMAND, 0x36);
    io_wait();

    /* Send divisor (low byte, high byte) */
    outb(PIT_CHANNEL0, divisor & 0xFF);
    io_wait();
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);

    terminal_writeString("PIT Initialised\n", STATUS_SUCCESS);
}