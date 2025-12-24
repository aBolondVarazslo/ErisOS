#include "terminal.h"
#include "idt/idt.h"
#include "debugging/debugging.h"

void kernel_main(void) {
    /* Initialise terminal interface */
    terminal_initialise();

    terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);
    terminal_writeString("Attempting to load filesystem...\n", STATUS_NORMAL);
    terminal_writeString("Filesystem not found!\n", STATUS_FAILURE);
    terminal_writeString("Testing...\n\n", STATUS_DEBUG);

    /* Load IDT */
    idt_init();

    /* Test IDT and ISR */
    trigger_debug_exception();
    trigger_breakpoint();

    trigger_divide_error();

    terminal_writeString("\nUpdate: 2025/12/24 @ 19:45\n", STATUS_DEBUG);

    while (1);
}