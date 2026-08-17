#include "../lib/terminal.h"
#include "../cpu/gdt/gdt.h"
#include "../cpu/idt/idt.h"
#include "../drivers/pic/pic.h"
#include "../drivers/pit/pit.h"
#include "../drivers/ps2/ps2.h"
#include "../apps/shell/shell.h"
#include "multiboot.h"
#include <stdint.h>

void kernel_main(uint32_t multiboot_info_ptr) {
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

    /* Initialise PS/2 */
    ps2_init();

    multiboot_info_t *mb_info = (multiboot_info_t *)multiboot_info_ptr;

    if (!(mb_info->flags & (1 << 6))) {
        terminal_writeString("Multiboot memory map not provided!\n", STATUS_FAILURE);
    }

    terminal_writeString("Lower mem (KB): ", STATUS_DEBUG);
    terminal_writeHex(mb_info->mem_lower);
    terminal_writeString("\nUpper mem (KB): ", STATUS_DEBUG);
    terminal_writeHex(mb_info->mem_higher);
    terminal_typeChar('\n', STATUS_DEBUG);

    multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t *)mb_info->mmap_addr;
    uint32_t offset = 0;

    while (offset < mb_info->mmap_length) {
        offset += entry->size + sizeof(entry->size);
        entry = (multiboot_mmap_entry_t *)((uint8_t *)entry + entry->size + sizeof(entry->size));
    }

    char buf[128];
    char *argv[MAX_ARGS];
    shell_run();
}