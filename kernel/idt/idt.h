#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* Exception vector constants */
#define IDT_DIVIDE_ERROR    0x00
#define IDT_DEBUG           0x01
#define IDT_NMI             0x02
#define IDT_BREAKPOINT      0x03
#define IDT_OVERFLOW        0x04
#define IDT_BOUND_RANGE     0x05
#define IDT_INVALID_OPCODE  0x06
#define IDT_DEVICE_NOT_AVAIL 0x07
#define IDT_DOUBLE_FAULT    0x08
/* REMEMBER TO ADD MORE EXCEPTIONS HERE LATER */

#define IDT_FLAG_PRESENT        0x80
#define IDT_FLAG_RING0          0x00
#define IDT_FLAG_RING3          0x60
#define IDT_FLAG_GATE_INTERRUPT 0x0E
#define IDT_FLAG_GATE_TRAP      0x0F

#define IDT_FLAG_KERNEL_INTERRUPT (IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_GATE_INTERRUPT)

/* 32-bit IDT entry */
struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

/* IDT pointer for lidt */
struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/* IDT array */
extern struct IDTEntry idt[256];

/* Function prototypes */
void idt_init(void);
void set_idt_entry(int n, uint32_t handler, uint16_t selector, uint8_t flags);

/* Array of ISR stubs */
extern void (*isr_stubs[6])(void);

#endif