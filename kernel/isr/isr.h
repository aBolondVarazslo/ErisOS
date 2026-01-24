#ifndef ISR_H
#define ISR_H

#include <stdint.h>

/* C handler for breakpoint interrupt */
void isr_debug_exception(void);
void isr_breakpoint(void);
void isr_common_handler(void);

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
static const char *interrupt_messages[] =
{
    "Divide Error",
    "Debug Exception",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "Floating-Point Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Error",
    "Virtualisation Exception",
    "Control Protection Exception",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
};

/* Assembly stubs that IDT uses */
extern void isr_debug_exception_stub(void);     /* 0x01 */
extern void isr_breakpoint_stub(void);          /* 0x03 */
extern void isr_common_stub(void);              /* Common stub */

extern void (*isr_stubs[3])(void);

#endif