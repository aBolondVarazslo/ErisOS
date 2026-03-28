#include "terminal.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "debugging/debugging.h"
#include "pic/pic.h"
#include "pit/pit.h"
#include "irq/irq.h"

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

    uint16_t cs16;
    asm volatile("mov %%cs, %0" : "=r"(cs16));
    set_idt_entry(0x20, (uint32_t)irq0_stub, cs16, IDT_FLAG_KERNEL_INTERRUPT);
    terminal_writeString("Forced IRQ stub\n", STATUS_DEBUG);

    terminal_writeString("irq0_stub address = ", STATUS_DEBUG);
    terminal_writeHex((uint32_t)irq0_stub);
    terminal_writeString("\n", STATUS_DEBUG);

    /* Remap PIC */
    PIC_remap(0x20, 0x28);
    PIC_set_mask(0xFE, 0xFF);

    /* Initialise PIT (IRQ0) */
    pit_init(100);
    //asm volatile("sti");
    terminal_writeString("Interrupts Enabled\n", STATUS_SUCCESS);

    terminal_writeString("\nUpdate: 2025/03/24 @ 20:36\n", STATUS_DEBUG);
    terminal_writeString("Reached end of kernel...\n", STATUS_NORMAL);

    while (1);
}