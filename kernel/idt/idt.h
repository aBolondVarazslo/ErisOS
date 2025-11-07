#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_DIVIDE_ERROR    0x00
#define IDT_BREAKPOINT      0x03

#define IDT_FLAG_PRESENT        0x80
#define IDT_FLAG_RING0          0x00
#define IDT_FLAG_RING3          0x60
#define IDT_FLAG_GATE_INTERRUPT 0x0E
#define IDT_FLAG_GATE_TRAP      0x0F

#define IDT_FLAG_KERNEL_INTERRUPT (IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_GATE_INTERRUPT)


/* 32-bit IDT entry struct */
struct IDTEntry {
    uint16_t offset_low;    /* Lower 16 bits */
    uint16_t selector;      /* Code segment selector */
    uint8_t zero;           /* Always 0 */
    uint8_t flags;          /* Type and attributes */
    uint16_t offset_high;   /* Upper 16 bits */
} __attribute__((packed));

/* IDT pointer for lidt */
struct IDTPointer {
    uint16_t limit;
    uint32_t base;          /* Will change to uint64_t if changing to 64-bit */
} __attribute__((packed));

/* IDT */
extern struct IDTEntry idt[256];

/* PROTOTYPE: Function */
void idt_init();            /* Sets up IDT */
void set_idt_entry(int n, uint32_t handler, uint16_t selector, uint8_t flags);

#endif