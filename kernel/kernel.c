#include "terminal.h"
#include "idt/idt.h"
#include "debugging/debugging.h"
#include "pic/pic.h"

void kernel_main(void) {
    /* Initialise terminal interface */
    terminal_initialise();

    terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);

    /* Load IDT */
    idt_init();

    /* Remap PIC */
    PIC_remap();
    PIC_set_mask(0xFE, 0xFF);

    terminal_writeString("\nUpdate: 2025/01/27 @ 16:40\n", STATUS_DEBUG);
    terminal_writeString("Reached end of kernel...\n", STATUS_NORMAL);

    while (1);
}