#include "heap.h"
#include "../pmm/pmm.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

static uint32_t heap_start;
static uint32_t heap_end;
static uint32_t heap_current;

void heap_init(uint32_t start_addr, uint32_t size) {
    heap_start = start_addr;
    heap_end = start_addr + size;
    heap_current = start_addr;
}

void *kmalloc(uint32_t size) {
    if (size > UINT32_MAX - 3u) {
        return NULL;
    }

    size = (size + 3u) & ~3u;
    if (size > heap_end - heap_current) {
        return NULL;
    }

    uint32_t curr_addr = heap_current;
    heap_current += size;
    return (void *)curr_addr;
}