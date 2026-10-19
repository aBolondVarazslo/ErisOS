#ifndef PAGING_H
#define PAGING_H

#define PAGE_PRESENT 0x1
#define PAGE_RW 0x2

#include <stdint.h>

typedef uint32_t page_directory_entry_t;
typedef uint32_t page_table_entry_t;

typedef page_directory_entry_t page_directory_t[1024];
typedef page_table_entry_t page_table_t[1024];

void paging_init(void);

#endif