#include "isr.h"
#include "../terminal.h"
#include "../vga.h"
#include <stdint.h>

void isr_divide_error(void) {
    terminal_writeString("Divide error!\n", STATUS_FAILURE);
    while(1);
}

void isr_breakpoint(void) {
    terminal_writeString("Breakpoint triggered.\n", STATUS_FAILURE);
}