#include "isr.h"
#include "../terminal.h"
#include "../vga.h"

/* C handlers */
void isr_debug_exception(void) {
    terminal_writeString("Debug exception.\n", STATUS_DEBUG);
}
void isr_breakpoint(void) {
    terminal_writeString("Breakpoint triggered.\n", STATUS_DEBUG);
}

void isr_common_handler(void) {
    terminal_writeString("Fatal Error!", STATUS_FAILURE);
    while (1);
}

/* Array of assembly stubs */
void (*isr_stubs[3])(void) = {
    isr_debug_exception_stub,               /* 0x01 */
    isr_breakpoint_stub,                    /* 0x03 */
    isr_common_stub,                        /* Common stub */
    };