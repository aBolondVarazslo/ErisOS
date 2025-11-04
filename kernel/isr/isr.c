#include "isr.h"
#include "../terminal.h"
#include "../vga.h"
#include <stdint.h>

void isr_breakpoint(void) {
    terminal_writeString("Breakpoint triggered.\n", STATUS_SUCCESS);
}