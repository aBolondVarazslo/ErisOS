#include "isr.h"
#include "../terminal.h"
#include "../vga.h"

/* C handlers */
void isr_debug_exception(void)
{
    terminal_writeString("Debug exception.\n", STATUS_DEBUG);
}
void isr_breakpoint(void)
{
    terminal_writeString("Breakpoint triggered.\n", STATUS_DEBUG);
}

void isr_common_handler(uint32_t int_no,
                        uint32_t err_code,
                        interrupt_stack_frame_t *frame)
{
    terminal_writeString("INTERRUPT: ", STATUS_FAILURE);

    if (int_no < 32)
    {
        terminal_writeString(interrupt_messages[int_no], STATUS_FAILURE);
    }
    else
    {
        terminal_writeString("Unknown Interrupt", STATUS_FAILURE);
    }

    terminal_writeString("\nError code: ", STATUS_FAILURE);
    terminal_writeHex(err_code);

    terminal_writeString("\nEIP: ", STATUS_FAILURE);
    terminal_writeHex(frame->eip);

    terminal_writeString("\nCS: ", STATUS_FAILURE);
    terminal_writeHex(frame->cs);

    terminal_writeString("\nEFLAGS: ", STATUS_FAILURE);
    terminal_writeHex(frame->eflags);

    while (1);
}

/* Array of assembly stubs */
void (*isr_stubs[32])(void) = {
    isr0_stub,
    isr_debug_exception_stub,               /* 0x01 */
    isr2_stub,
    isr_breakpoint_stub,                    /* 0x03 */
    isr4_stub,
    isr5_stub,
    isr6_stub,
    isr7_stub,
    isr8_stub,
    isr9_stub,
    isr10_stub,
    isr11_stub,
    isr12_stub,
    isr13_stub,
    isr14_stub,
    isr15_stub,
    isr16_stub,
    isr17_stub,
    isr18_stub,
    isr19_stub,
    isr20_stub,
    isr21_stub,
    isr22_stub,
    isr23_stub,
    isr24_stub,
    isr25_stub,
    isr26_stub,
    isr27_stub,
    isr28_stub,
    isr29_stub,
    isr30_stub,
    isr31_stub,
};