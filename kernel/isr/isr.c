#include "isr.h"
#include "../terminal.h"
#include "../vga.h"

/* C handlers */
void isr_divide_error(void) {
    terminal_writeString("Divide error!\n", STATUS_FAILURE);
}

void isr_debug_exception(void) {
    terminal_writeString("Debug exception.\n", STATUS_DEBUG);
}

void isr_nmi(void) {
    terminal_writeString("Non-maskable interrupt!\n", STATUS_FAILURE);
}

void isr_breakpoint(void) {
    terminal_writeString("Breakpoint triggered.\n", STATUS_DEBUG);
}

void isr_overflow(void) {
    terminal_writeString("Overflow!", STATUS_FAILURE);
}

/* Array of assembly stubs */
void (*isr_stubs[5])(void) = {
    isr_divide_error_stub,                  /* 0x00 */
    isr_debug_exception_stub,               /* 0x01 */
    isr_nmi_stub,                           /* 0x02 */
    isr_breakpoint_stub,                    /* 0x03 */
    isr_overflow_stub                       /* 0x04 */
    };