#include "paging.h"
#include "pmm.h"
#include "../lib/terminal.h"
#include <stdint.h>

static inline void load_page_directory(uint32_t dir_addr) {
    asm volatile("mov %0, %%cr3" : : "r"(dir_addr));
}

static inline void enable_paging(void) {
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; /* Set the paging bit (bit 31) */
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

static inline uint32_t read_cr0(void) {
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    return cr0;
}

void paging_init(void) {
    /* Initialise paging structures and enable paging */
    uint32_t dir_addr = pmm_alloc_frame();
    page_directory_t *page_directory = (page_directory_t *)dir_addr;

    /* Initialise the page directory */
    for (uint32_t i = 0; i < 1024; i++) {
        (*page_directory)[i] = 0;
    }

    /* Build page with identity mapping */
    uint32_t table_addr = pmm_alloc_frame();
    page_table_t *page_table = (page_table_t *)table_addr;

    for (uint32_t i = 0; i < 1024; i++) {
        uint32_t frame_addr = i * FRAME_SIZE;
        (*page_table)[i] = frame_addr | PAGE_PRESENT | PAGE_RW;
    }

    /* Set the first entry of the page directory to point to the page table */
    (*page_directory)[0] = table_addr | PAGE_PRESENT | PAGE_RW;

    /* Load the page directory into CR3 and enable paging */
    load_page_directory(dir_addr);
    enable_paging();

    if (read_cr0() & 0x80000000) {
        /* Paging is enabled */
        terminal_writeString("Paging Enabled\n", STATUS_SUCCESS);
    } else {
        /* Paging failed to enable */
        terminal_writeString("Paging Failed\n", STATUS_FAILURE);
    }
}