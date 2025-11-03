#include "idt.h"
#include "../terminal.h"
#include "../vga.h"

/* IDT */
struct IDTEntry idt[256];
struct IDTPointer idt_ptr;

extern void isr_dummy();

/* Fills one IDT entry */
void set_idt_entry(int n, uint32_t handler, uint16_t selector, uint8_t flags) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = selector;
    idt[n].zero = 0;
    idt[n].flags = flags;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

/* Initialise IDT */
void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    set_idt_entry(0x03, (uint32_t)isr_dummy, 0x08, 0x8E);

    /* Load IDT */
    asm volatile("lidt (%0)" : : "m" (idt_ptr));
    terminal_writeString("IDT Initialised.\n", STATUS_SUCCESS);
}