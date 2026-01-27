#ifndef ISR_H
#define ISR_H

#include <stdint.h>

/* C handler for breakpoint interrupt */
void isr_debug_exception(void);
void isr_breakpoint(void);
void isr_common_handler();

/* CPU registers saved on stack during an interrupt
   Packed to match exact memory layout of stack on interrupt */
typedef struct __attribute__((packed)) {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} interrupt_stack_frame_t;

/* Strings to be displayed during interrupt handler */
const char *interrupt_messages[32] = {
    "Divide Error",                     /* 0x00 */
    "Debug Exception",                  /* 0x01 */
    "Non-Maskable Interrupt",           /* 0x02 */
    "Breakpoint",                       /* 0x03 */
    "Overflow",                         /* 0x04 */
    "BOUND Range Exceeded",             /* 0x05 */
    "Invalid Opcode",                   /* 0x06 */
    "Device Not Available",             /* 0x07 */
    "Double Fault",                     /* 0x08 */
    "Coprocessor Segment Overrun",      /* 0x09 */
    "Invalid TSS",                      /* 0x0A */
    "Segment Not Present",              /* 0x0B */
    "Stack-Segment Fault",              /* 0x0C */
    "General Protection Fault",         /* 0x0D */
    "Page Fault",                       /* 0x0E */
    "Reserved",                         /* 0x0F */
    "x87 Floating-Point Error",         /* 0x10 */
    "Alignment Check",                  /* 0x11 */
    "Machine Check",                    /* 0x12 */
    "SIMD Floating-Point Exception",    /* 0x13 */
    "Virtualisation Exception",         /* 0x14 */
    "Control Protection Exception",     /* 0x15 */
    "Reserved",                         /* 0x16 */
    "Reserved",                         /* 0x17 */
    "Reserved",                         /* 0x18 */
    "Reserved",                         /* 0x19 */
    "Reserved",                         /* 0x1A */
    "Reserved",                         /* 0x1B */
    "Reserved",                         /* 0x1C */
    "Reserved",                         /* 0x1D */
    "Reserved",                         /* 0x1E */
    "Reserved"                          /* 0x1F */
};

/* Assembly stubs that IDT uses */
extern void isr0_stub(void);
extern void isr_debug_exception_stub(void);     /* 0x01 */
extern void isr2_stub(void);
extern void isr_breakpoint_stub(void);          /* 0x03 */
extern void isr4_stub(void);
extern void isr5_stub(void);
extern void isr6_stub(void);
extern void isr7_stub(void);
extern void isr8_stub(void);
extern void isr9_stub(void);
extern void isr10_stub(void);
extern void isr11_stub(void);
extern void isr12_stub(void);
extern void isr13_stub(void);
extern void isr14_stub(void);
extern void isr15_stub(void);
extern void isr16_stub(void);
extern void isr17_stub(void);
extern void isr18_stub(void);
extern void isr19_stub(void);
extern void isr20_stub(void);
extern void isr21_stub(void);
extern void isr22_stub(void);
extern void isr23_stub(void);
extern void isr24_stub(void);
extern void isr25_stub(void);
extern void isr26_stub(void);
extern void isr27_stub(void);
extern void isr28_stub(void);
extern void isr29_stub(void);
extern void isr30_stub(void);
extern void isr31_stub(void);

extern void (*isr_stubs[32])(void);

#endif