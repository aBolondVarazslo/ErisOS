#include "terminal.h"
#include "idt/idt.h"
#include "debugging/debugging.h"
#include "pic/pic.h"
#include "pit/pit.h"

void kernel_main(void) {
    /* Initialise terminal interface */
    terminal_initialise();

    terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);

    /* Load IDT */
    idt_init();

    /* Remap PIC */
    PIC_remap(0x20, 0x28);
    PIC_set_mask(0xFE, 0xFF);

    /* Initialise PIT (IRQ0) */
    pit_init(100);
    asm volatile("int $0x20");
    //asm volatile("sti");
    terminal_writeString("Interrupts Enabled\n", STATUS_SUCCESS);

    terminal_writeString("\nUpdate: 2025/03/22 @ 23:26\n", STATUS_DEBUG);
    terminal_writeString("Reached end of kernel...\n", STATUS_NORMAL);

    while (1);
}