#ifndef ISR_H
#define ISR_H

#include <stdint.h>

/* C handler for breakpoint interrupt */
void isr_debug_exception(void);
void isr_breakpoint(void);
void isr_common_handler();

/* CPU registers saved on stack during an interrupt
   Packed to match exact memory layout of stack on interrupt */
typedef struct __attribute__((packed))
{
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} interrupt_stack_frame_t;

/* Strings to be displayed during interrupt handler */
static const char *interrupt_messages[32] =
{
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
    "Invalid TSS",                      /* 0x10 */
    "Segment Not Present",              /* 0x11 */
    "Stack-Segment Fault",              /* 0x12 */
    "General Protection Fault",         /* 0x13 */
    "Page Fault",                       /* 0x14 */
    "Reserved",                         /* 0x15 */
    "x87 Floating-Point Error",         /* 0x16 */
    "Alignment Check",                  /* 0x17 */
    "Machine Check",                    /* 0x18 */
    "SIMD Floating-Point Error",        /* 0x19 */
    "Virtualisation Exception",         /* 0x20 */
    "Control Protection Exception",     /* 0x21 */
    "Hypervisor Injection Exception",   /* 0x22 */
    "VMM Communication Exception",      /* 0x23 */
    "Security Exception",               /* 0x24 */
    "Reserved",                         /* 0x25 */
    "Reserved",                         /* 0x26 */
    "Reserved",                         /* 0x27 */
    "Reserved",                         /* 0x28 */
    "Reserved",                         /* 0x29 */
    "Reserved",                         /* 0x30 */
    "Reserved",                         /* 0x31 */
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

extern void (*isr_stubs[25])(void);

#endif