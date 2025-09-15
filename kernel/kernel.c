#include "terminal.h"

void kernel_main(void)
{
        /* Initialise terminal interface */
        terminal_initialise();

        terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);
        terminal_writeString("Attempting to load filesystem...\n", STATUS_NORMAL);
        terminal_writeString("Filesystem not found!\n", STATUS_FAILURE);
        terminal_writeString("Testing...\n", STATUS_DEBUG);
        terminal_writeString("Tabs\tend here.\n", STATUS_DEBUG);
        terminal_writeString("Backk\bspace.\n", STATUS_DEBUG);
        terminal_writeString("Not a\rReturn function.\n", STATUS_DEBUG);
        
        
        for (int i = 0; i < 50; i++)
        {
                terminal_writeString("Testing...\n", STATUS_DEBUG);
        }

        terminal_writeString("Post for loop...\n", STATUS_DEBUG);
}