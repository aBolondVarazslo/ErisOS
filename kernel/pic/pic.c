#include "pic.h"
#include <stdint.h>

/* Send byte ("value") to I/O port ("port") */
static inline void outb(uint16_t port, uint8_t value) {
    /* "outb %0, %1" -> Sends AL register (%0) to port (%1) */
    /* "=a"(value) -> Puts "value" into the AL register (lower 8 bits of EAX) */
    /* "Nd"(port) -> Makes port 8-bit immediate or DX register */
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

/* Read byte from I/O port ("port") */
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    /* "inb %1, %0" -> Reads from port (%1) into AL register (%0) */
    /* "=a"(ret) -> Stores result from AL register into "ret" */
    /* "Nd"(port) -> Makes port 8-bit immediate or DX register */
    asm volatile("inb %1, %0" : : "=a"(ret), "Nd"(port));
}

/* Small delay for older PIC hardware. Ensures the PIC has time to process commands */
static inline void io_wait(void) {
    /* Ouput to port 0x80 is used as tiny delay */
    asm volatile("outb %%al, $0x80" : : "a"(0));
}