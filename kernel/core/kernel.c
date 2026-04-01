#include "../lib/terminal.h"
#include "../cpu/gdt/gdt.h"
#include "../cpu/idt/idt.h"
#include "../debugging/debugging.h"
#include "../drivers/pic/pic.h"
#include "../drivers/pit/pit.h"
#include "../cpu/irq/irq.h"

void kernel_main(void) {
    /* Initialise terminal interface */
    terminal_initialise();

    terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);

    /* Prevent GDT OK message from being overwritten by IDT Initialised message */
    terminal_writeString("\n", STATUS_DEBUG);

    /* Setup GDT */
    gdt_init();

    /* Load IDT */
    idt_init();

    /* Remap PIC */
    PIC_remap(0x20, 0x28);
    PIC_set_mask(0x00, 0x00);

    /* Initialise PIT (IRQ0) */
    pit_init(100);
    asm volatile("sti");
    terminal_writeString("Interrupts Enabled\n", STATUS_SUCCESS);

    terminal_writeString("\nUpdate: 2026/04/01 @ 21:32\n", STATUS_DEBUG);
    terminal_writeString("Reached end of kernel...\n", STATUS_NORMAL);

    while (1);
}