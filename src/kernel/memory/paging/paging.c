#include "paging.h"
#include "../pmm/pmm.h"
#include "../memlayout/memlayout.h"
#include "../../lib/terminal.h"
#include <stdint.h>

static inline void load_page_directory(uint32_t dir_addr) {
    asm volatile("mov %0, %%cr3" : : "r"(dir_addr));
}

void paging_init(void) {
    /* Initialise paging structures and enable paging */
    uint32_t dir_addr = pmm_alloc_frame();
    page_directory_t *page_directory = (page_directory_t *)PHYS_TO_VIRT(dir_addr);

    /* Initialise the page directory */
    for (uint32_t i = 0; i < 1024; i++) {
        (*page_directory)[i] = 0;
    }

    /* Build page with identity mapping */
    uint32_t total_frames = pmm_get_highest_frame();
    uint32_t num_tables = (total_frames + 1023) / 1024;

    if (num_tables > 256) {
        num_tables = 256;
    }

    for (uint32_t t = 0; t < num_tables; t++) {
        uint32_t table_addr = pmm_alloc_frame();
        page_table_t *page_table = (page_table_t *)PHYS_TO_VIRT(table_addr);

        for (uint32_t i = 0; i < 1024; i++) {
            uint32_t frame_number = t * 1024 + i;
            uint32_t frame_addr = frame_number * FRAME_SIZE;
            (*page_table)[i] = frame_addr | PAGE_PRESENT | PAGE_RW;
        }

        (*page_directory)[(KERNEL_VMA >> 22) + t] = table_addr | PAGE_PRESENT | PAGE_RW;
    }

    /* Load the page directory into CR3 and enable paging */
    load_page_directory(dir_addr);
    terminal_writeString("Paging Enabled\n", STATUS_SUCCESS);
}