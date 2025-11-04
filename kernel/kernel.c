#include "terminal.h"
#include "idt/idt.h"

void kernel_main(void)
{
    /* Initialise terminal interface */
    terminal_initialise();

    terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);
    terminal_writeString("Attempting to load filesystem...\n", STATUS_NORMAL);
    terminal_writeString("Filesystem not found!\n", STATUS_FAILURE);
    terminal_writeString("Testing...\n\n", STATUS_DEBUG);

    
    /* Load IDT */
    idt_init();
    
    /* Test IDT and ISR */
    asm volatile("int $0x03");
    
    
    terminal_writeString("\nUpdate: 2025/11/04 @ 21:46\n", STATUS_DEBUG);
    
    
    while(1);
}