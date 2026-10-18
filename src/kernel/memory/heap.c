#include "heap.h"
#include "pmm.h"
#include <stdint.h>
#include <stddef.h>

static uint32_t heap_start;
static uint32_t heap_end;
static uint32_t heap_current;

void heap_init(uint32_t start_addr, uint32_t size) {
    heap_start = start_addr;
    heap_end = start_addr + size;
    heap_current = start_addr;
}

void *kmalloc(uint32_t size) {
    if (size > heap_end - heap_current) {
        return NULL;
    }

    uint32_t curr_addr = heap_current;
    heap_current += size;
    return (void *)curr_addr;
}